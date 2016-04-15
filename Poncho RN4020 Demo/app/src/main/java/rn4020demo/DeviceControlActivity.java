/*
 * Copyright (C) 2014 Microchip Technology Inc. and its subsidiaries.  You may use this software and any derivatives
 * exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
 * SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE,
 * COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF
 * THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON
 * ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * This file includes code modified from "The Android Open Source Project" copyright (C) 2013.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 
 */

package rn4020demo;

import java.util.List;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.util.TypedValue;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import java.util.UUID;

/**
 * This Activity receives a Bluetooth device address provides the user interface to connect, display data, and display GATT services
 * and characteristics supported by the device. The Activity communicates with {@code BluetoothLeService}, which in turn
 * interacts with the Bluetooth LE API.
 */
public class DeviceControlActivity extends Activity {

    private final static String TAG = DeviceControlActivity.class.getSimpleName();      //Get name of activity to tag debug and warning messages

    public static final String EXTRAS_DEVICE_NAME = "DEVICE_NAME";                      //Name passed by intent that lanched this activity
    public static final String EXTRAS_DEVICE_ADDRESS = "DEVICE_ADDRESS";                //MAC address passed by intent that lanched this activity

    private static final String MLDP_PRIVATE_SERVICE = "00035b03-58e6-07dd-021a-08123a000300"; //Private service for Microchip MLDP
    private static final String MLDP_DATA_PRIVATE_CHAR = "00035b03-58e6-07dd-021a-08123a000301"; //Characteristic for MLDP Data, properties - notify, write
    private static final String MLDP_CONTROL_PRIVATE_CHAR = "00035b03-58e6-07dd-021a-08123a0003ff"; //Characteristic for MLDP Control, properties - read, write
    private static final String CHARACTERISTIC_NOTIFICATION_CONFIG = "00002902-0000-1000-8000-00805f9b34fb";	//Special UUID for descriptor needed to enable notifications

    private BluetoothAdapter mBluetoothAdapter;                                         //BluetoothAdapter controls the Bluetooth radio in the phone
    private BluetoothGatt mBluetoothGatt;                                               //BluetoothGatt controls the Bluetooth communication link
    private BluetoothGattCharacteristic mDataMDLP, mControlMLDP;                        //The BLE characteristic used for MLDP data transfers
    private Handler mHandler;                                                           //Handler used to send die roll after a time delay
    
    private TextView mConnectionState;                                      //TextViews to show connection state and die roll number on the display

    private SeekBar led0R;
    private SeekBar led0G;
    private SeekBar led0B;
    private Switch led1;
    private Switch led2;
    private Switch led3;

    private String mDeviceName, mDeviceAddress;                                         //Strings for the Bluetooth device name and MAC address
    private String incomingMessage;                                                     //String to hold the incoming message from the MLDP characteristic
    private boolean mConnected = false;                                                 //Indicator of an active Bluetooth connection
    private boolean writeComplete = false;                                              //Indicator that the characteristic write has completed (for reference - not used)

    // ----------------------------------------------------------------------------------------------------------------
    // Activity launched
    // Invoked by Intent in onListItemClick method in DeviceScanActivity
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.device_control);                                            //Show the screen with the die number and button

        final Intent intent = getIntent();                                              //Get the Intent that launched this activity 
        mDeviceName = intent.getStringExtra(EXTRAS_DEVICE_NAME);                        //Get the BLE device name from the Intent
        mDeviceAddress = intent.getStringExtra(EXTRAS_DEVICE_ADDRESS);                  //Get the BLE device address from the Intent
        mHandler = new Handler();                                                       //Create Handler to delay sending first roll after new connection

        ((TextView) findViewById(R.id.deviceAddress)).setText(mDeviceAddress);          //Display device address on the screen
        mConnectionState = (TextView) findViewById(R.id.connectionState);               //TextView that will display the connection state

        led0R = (SeekBar) findViewById(R.id.led0r);
        led0G = (SeekBar) findViewById(R.id.led0g);
        led0B = (SeekBar) findViewById(R.id.led0b);
        led1 = (Switch) findViewById(R.id.led1);
        led2 = (Switch) findViewById(R.id.led2);
        led3 = (Switch) findViewById(R.id.led3);

        incomingMessage = new String();                                                 //Create new string to hold incoming message data
        this.getActionBar().setTitle(mDeviceName);                                      //Set the title of the ActionBar to the name of the BLE device 
        this.getActionBar().setDisplayHomeAsUpEnabled(true);                            //Make home icon clickable with < symbol on the left 

        led1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b)
                    mDataMDLP.setValue("ON,LED1\r\n");
                else
                    mDataMDLP.setValue("OFF,LED1\r\n");
                mBluetoothGatt.writeCharacteristic(mDataMDLP);
            }
        });

        led2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b)
                    mDataMDLP.setValue("ON,LED2\r\n");
                else
                    mDataMDLP.setValue("OFF,LED2\r\n");
                mBluetoothGatt.writeCharacteristic(mDataMDLP);
            }
        });

        led3.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if (b)
                    mDataMDLP.setValue("ON,LED3\r\n");
                else
                    mDataMDLP.setValue("OFF,LED3\r\n");
                mBluetoothGatt.writeCharacteristic(mDataMDLP);
            }
        });

        final BluetoothManager bluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE); //Get the BluetoothManager
        mBluetoothAdapter = bluetoothManager.getAdapter();                              //Get a reference to the BluetoothAdapter (radio)
        if (mBluetoothAdapter == null) {                                                //Check if we got the BluetoothAdapter
            Toast.makeText(this, R.string.bluetooth_not_supported, Toast.LENGTH_SHORT).show(); //Message that Bluetooth is not supported
            finish();                                                                   //End the activity
        }
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Activity resumed
    @Override
    protected void onResume() {
        super.onResume();

        if (mBluetoothAdapter == null || mDeviceAddress == null) {                      //Check that we still have a Bluetooth adappter and device address 
            Log.w(TAG, "BluetoothAdapter not initialized or unspecified address.");     //Warn that something went wrong
            finish();                                                                   //End the Activity
        }

/*      if (mBluetoothGatt != null) {                                                   //See if there is a previous connection
            Log.d(TAG, "Trying to use an existing mBluetoothGatt for connection.");
            if (mBluetoothGatt.connect()) {                                             //Try to reconnect to the previous device
                Log.w(TAG, "Existing Gatt unable to connect.");                         //Warn that something went wrong
                finish();                                                               //Attempt failed so end the Activity
            }
        }
*/
        final BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(mDeviceAddress); //Get the Bluetooth device by referencing its address
        if (device == null) {                                                           //Check whether a device was returned
            Log.w(TAG, "Device not found.  Unable to connect.");                        //Warn that something went wrong
            finish();                                                                   //End the Activity
        }
        mBluetoothGatt = device.connectGatt(this, false, mGattCallback);                //Directly connect to the device so autoConnect is false
        Log.d(TAG, "Trying to create a new connection.");
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Activity paused
    @Override
    protected void onPause() {
        super.onPause();
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Activity is ending
    @Override
    protected void onDestroy() {
        super.onDestroy();
        mBluetoothGatt.disconnect();                                                    //Activity is ending so disconnect from Bluetooth device
        mBluetoothGatt.close();                                                         //Close the connection
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Options menu is different depending on whether connected or not
    // Show Connect option if not connected or show Disconnect option if we are connected
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.gatt_services, menu);                          //Show the Options menu
        if (mConnected) {                                                               //See if connected
            menu.findItem(R.id.menu_connect).setVisible(false);                         // then dont show disconnect option
            menu.findItem(R.id.menu_disconnect).setVisible(true);                       // and do show connect option
        }
        else {                                                                          //If not connected    
            menu.findItem(R.id.menu_connect).setVisible(true);                          // then show connect option
            menu.findItem(R.id.menu_disconnect).setVisible(false);                      // and don't show disconnect option
        }
        return true;
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Menu item selected
    // Connect or disconnect to BLE device
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {                                                     //Get which menu item was selected
            case R.id.menu_connect:                                                     //Option to Connect chosen
                if(mBluetoothGatt != null) {                                            //If there is a valid GATT connection
                    mBluetoothGatt.connect();                                           // then connect
                }
                return true;
            case R.id.menu_disconnect:                                                  //Option to Disconnect chosen
                if(mBluetoothGatt != null) {                                            //If there is a valid GATT connection
                    mBluetoothGatt.disconnect();                                        // then disconnect
                }
                return true;
            case android.R.id.home:                                                     //Option to go back was chosen
                onBackPressed();                                                        //Execute functionality of back button
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Update text with connection state
    private void updateConnectionState(final int resourceId) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mConnectionState.setText(resourceId);                                   //Update text to say "Connected" or "Disconnected"
            }
        });
    }
    
    // ----------------------------------------------------------------------------------------------------------------
    // Look for message with switch pressed indicator "->S1\n\r"
    private void processIncomingPacket(String data) {
        char switchState;
        int indexStart, indexEnd;
        incomingMessage = incomingMessage.concat(data);                                 //Add the new data to what is left of previous data
        if (incomingMessage.length() >= 6 && incomingMessage.contains("=>S") && incomingMessage.contains("\r\n")) { //See if we have the right nessage
            indexStart = incomingMessage.indexOf("=>S");                                //Get the position of the matching characters
            indexEnd = incomingMessage.indexOf("\r\n");                                 //Get the position of the end of frame "\r\n"
            if (indexEnd - indexStart == 4) {                                           //Check that the packet does not have missing or extra characters 
                switchState = incomingMessage.charAt(indexStart + 3);                   //Get the character that represents the switch being pressed
                if (switchState == '1') {                                               //Is it a "1"
                    // if so then update the state of the die with a new roll and send over BLE
                }
            }
            incomingMessage = incomingMessage.substring(indexEnd + 2);                  //Thow away everything up to and including "\n\r" 
        }
        else if (incomingMessage.contains("\r\n")) {                                    //See if we have an end of frame "\r\n" without a valid message
            incomingMessage = incomingMessage.substring(incomingMessage.indexOf("\r\n") + 2); //Thow away everything up to and including "\n\r" 
        }
    }

    /** Listeners */


    // ----------------------------------------------------------------------------------------------------------------
    // Iterate through the supported GATT Services/Characteristics to see if the MLDP srevice is supported
    private void findMldpGattService(List<BluetoothGattService> gattServices) {
        if (gattServices == null) {                                                     //Verify that list of GATT services is valid
            Log.d(TAG, "findMldpGattService found no Services");
            return;
        }
        String uuid;                                                                    //String to compare received UUID with desired known UUIDs
        mDataMDLP = null;                                                               //Searching for a characteristic, start with null value

        for (BluetoothGattService gattService : gattServices) {                         //Test each service in the list of services
            uuid = gattService.getUuid().toString();                                    //Get the string version of the service's UUID
            if (uuid.equals(MLDP_PRIVATE_SERVICE)) {                                    //See if it matches the UUID of the MLDP service 
                List<BluetoothGattCharacteristic> gattCharacteristics = gattService.getCharacteristics(); //If so then get the service's list of characteristics
                for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) { //Test each characteristic in the list of characteristics
                    uuid = gattCharacteristic.getUuid().toString();                     //Get the string version of the characteristic's UUID
                    if (uuid.equals(MLDP_DATA_PRIVATE_CHAR)) {                          //See if it matches the UUID of the MLDP data characteristic
                        mDataMDLP = gattCharacteristic;                                 //If so then save the reference to the characteristic 
                        Log.d(TAG, "Found MLDP data characteristics");
                    } 
                    else if (uuid.equals(MLDP_CONTROL_PRIVATE_CHAR)) {                  //See if UUID matches the UUID of the MLDP control characteristic
                        mControlMLDP = gattCharacteristic;                              //If so then save the reference to the characteristic 
                        Log.d(TAG, "Found MLDP control characteristics");
                    }
                    final int characteristicProperties = gattCharacteristic.getProperties(); //Get the properties of the characteristic
                    if ((characteristicProperties & (BluetoothGattCharacteristic.PROPERTY_NOTIFY)) > 0) { //See if the characteristic has the Notify property
                        mBluetoothGatt.setCharacteristicNotification(gattCharacteristic, true); //If so then enable notification in the BluetoothGatt
                        BluetoothGattDescriptor descriptor = gattCharacteristic.getDescriptor(UUID.fromString(CHARACTERISTIC_NOTIFICATION_CONFIG)); //Get the descripter that enables notification on the server
                        descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE); //Set the value of the descriptor to enable notification
                        mBluetoothGatt.writeDescriptor(descriptor);                     //Write the descriptor
                    }
                    if ((characteristicProperties & (BluetoothGattCharacteristic.PROPERTY_INDICATE)) > 0) { //See if the characteristic has the Indicate property
                        mBluetoothGatt.setCharacteristicNotification(gattCharacteristic, true); //If so then enable notification (and indication) in the BluetoothGatt
                        BluetoothGattDescriptor descriptor = gattCharacteristic.getDescriptor(UUID.fromString(CHARACTERISTIC_NOTIFICATION_CONFIG)); //Get the descripter that enables indication on the server
                        descriptor.setValue(BluetoothGattDescriptor.ENABLE_INDICATION_VALUE); //Set the value of the descriptor to enable indication
                        mBluetoothGatt.writeDescriptor(descriptor);                     //Write the descriptor
                    }
                    if ((characteristicProperties & (BluetoothGattCharacteristic.PROPERTY_WRITE)) > 0) { //See if the characteristic has the Write (acknowledged) property
                        gattCharacteristic.setWriteType(BluetoothGattCharacteristic.WRITE_TYPE_DEFAULT); //If so then set the write type (write with acknowledge) in the BluetoothGatt
                    }
                    if ((characteristicProperties & (BluetoothGattCharacteristic.PROPERTY_WRITE_NO_RESPONSE)) > 0) { //See if the characteristic has the Write (unacknowledged) property
                        gattCharacteristic.setWriteType(BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE); //If so then set the write type (write with no acknowledge) in the BluetoothGatt
                    }
                }
                break;                                                                  //Found the MLDP service and are not looking for any other services
            }
        }
        if (mDataMDLP == null) {                                                        //See if the MLDP data characteristic was not found
            Toast.makeText(this, R.string.mldp_not_supported, Toast.LENGTH_SHORT).show(); //If so then show an error message
            Log.d(TAG, "findMldpGattService found no MLDP service");
            finish();                                                                   //and end the activity
        }
        mHandler.postDelayed(new Runnable() { //Create delayed runnable that will send a roll of the die after a delay
            @Override
            public void run() {
                       //Update the state of the die with a new roll and send over BLE
            }
        }, 200);       //Do it after 200ms delay to give the RN4020 time to configure the characteristic
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Implements callback methods for GATT events that the app cares about.  For example: connection change and services discovered.
    // When onConnectionStateChange() is called with newState = STATE_CONNECTED then it calls mBluetoothGatt.discoverServices()
    // resulting in another callback to onServicesDiscovered()
    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) { //Change in connection state
            if (newState == BluetoothProfile.STATE_CONNECTED) {                         //See if we are connected
                Log.i(TAG, "Connected to GATT server.");
                mConnected = true;                                                      //Record the new connection state
                updateConnectionState(R.string.connected);                              //Update the display to say "Connected"
                invalidateOptionsMenu();                                                //Force the Options menu to be regenerated to show the disconnect option
                mBluetoothGatt.discoverServices();                                      // Attempt to discover services after successful connection.
            } 
            else if (newState == BluetoothProfile.STATE_DISCONNECTED) {                 //See if we are not connected
                Log.i(TAG, "Disconnected from GATT server.");
                mConnected = false;                                                     //Record the new connection state
                updateConnectionState(R.string.disconnected);                           //Update the display to say "Disconnected"
                invalidateOptionsMenu();                                                //Force the Options menu to be regenerated to show the connect option
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {              //Service discovery complete
            if (status == BluetoothGatt.GATT_SUCCESS && mBluetoothGatt != null) {       //See if the service discovery was successful
                findMldpGattService(mBluetoothGatt.getServices());                      //Get the list of services and call method to look for MLDP service
            } 
            else {                                                                      //Service discovery was not successful
                Log.w(TAG, "onServicesDiscovered received: " + status);
            }
        }

        //For information only. This application uses Indication to receive updated characteristic data, not Read
        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) { //A request to Read has completed
            if (status == BluetoothGatt.GATT_SUCCESS) {                                 //See if the read was successful
            String dataValue = characteristic.getStringValue(0);                        //Get the value of the characteristic
            processIncomingPacket(dataValue);                                           //Process the data that was received
            }
        }

        //For information only. This application sends small packets infrequently and does not need to know what the previous write completed
        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) { //A request to Write has completed
            if (status == BluetoothGatt.GATT_SUCCESS) {                                 //See if the write was successful
                writeComplete = true;                                                   //Record that the write has completed
            }
        }

        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) { //Indication or notification was received
            String dataValue = characteristic.getStringValue(0);                        //Get the value of the characteristic
            processIncomingPacket(dataValue);                                           //Process the data that was received
        }
    };


    // ----------------------------------------------------------------------------------------------------------------
    // Request a read of a given BluetoothGattCharacteristic. The Read result is reported asynchronously through the
    // BluetoothGattCallback onCharacteristicRead callback method.
    // For information only. This application uses Indication to receive updated characteristic data, not Read
    
    private void readCharacteristic(BluetoothGattCharacteristic characteristic) {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {                      //Check that we have access to a Bluetooth radio
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.readCharacteristic(characteristic);                              //Request the BluetoothGatt to Read the characteristic
    }

    // ----------------------------------------------------------------------------------------------------------------
    // Write to a given characteristic. The completion of the write is reported asynchronously through the
    // BluetoothGattCallback onCharacteristicWrire callback method.
    private void writeCharacteristic(BluetoothGattCharacteristic characteristic) {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {                      //Check that we have access to a Bluetooth radio
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        int test = characteristic.getProperties();                                      //Get the properties of the characteristic
        if ((test & BluetoothGattCharacteristic.PROPERTY_WRITE) == 0 && (test & BluetoothGattCharacteristic.PROPERTY_WRITE_NO_RESPONSE) == 0) { //Check that the property is writable 
            return;
        }

        if (mBluetoothGatt.writeCharacteristic(characteristic)) {                       //Request the BluetoothGatt to do the Write
            Log.d(TAG, "writeCharacteristic successful");                               //The request was accepted, this does not mean the write completed
        } 
        else {
            Log.d(TAG, "writeCharacteristic failed");                                   //Write request was not accepted by the BluetoothGatt
        }
    }

}
