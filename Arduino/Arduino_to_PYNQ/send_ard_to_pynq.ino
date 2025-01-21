#include <Wire.h>

#define SLAVE_ADDRESS 0x18
#define ROWS 2       // Number of rows in the 2D array
#define COLS 72      // Number of columns in the 2D array
#define CHUNK_SIZE 32 // Number of bytes sent per chunk
#define FLOAT_SIZE 4  // Size of a float in bytes

float data_array[ROWS][COLS] = {{0.227903, 0.649318, 0.163460, -0.215824, 0.143550, 0.279111, -0.018451, 0.079685, 0.488819, 0.134776, 0.150705, -0.073882, 0.109455, 0.437366, 0.561114, -0.165506, 0.625000, 0.437500, 0.479129, -0.007118, -0.297386, 0.240851, -0.252288, -0.159748, -0.370247, -0.141967, -0.364246, -0.004270, -0.154075, -0.152424, 0.101868, -0.177307, 0.386374, 0.394876, -0.065271, 0.001564, -0.210734, 0.202604, -0.210512, 0.066845, -0.208288, 0.107957, 0.243290, -0.067017, 0.594131, -0.244922, 0.148171, -0.557415, 0.531250, -0.031250, -0.045249, 0.066111, -0.086231, 0.126514, 0.604667, 0.055153, -0.559462, -0.009199, 0.018724, -0.162301, 0.490165, -0.005896, 0.078138, -0.032547, 0.272097, 0.163182, -0.133985, -0.282296, 0.220927, -0.656120, 0.310549, -0.120506},
  {0.239735, -0.072276, -0.019746, 0.367609, -0.371162, 0.062410, -0.212178, 0.122502, 0.750000, 0.625000, -0.066728, -0.071151, 0.422870, 0.231829, -0.184836, -0.204809, -0.093141, -0.185698, -0.112747, -0.155004, -0.006529, -0.088361, -0.025779, 0.371931, -0.011374, 0.792624, -0.445958, 0.217751, 0.288199, -0.444314, -0.225092, 0.280802, 0.229734, -0.045457, 0.095897, -0.246525, -0.067258, 0.187088, -0.150651, 0.186315, 0.218750, -0.031250, 0.114602, 0.290962, -0.481195, 0.019524, -0.024037, 0.002578, 0.272850, 0.211864, -0.011878, 0.341389, -0.594726, -0.195260, -0.500683, 0.252028, 0.227903, 0.649318, 0.163460, -0.215824, 0.143550, 0.279111, -0.018451, 0.079685, 0.488819, 0.134776, 0.150705, -0.073882, 0.109455, 0.437366, 0.561114, -0.165506}};
        ; // Example 2D array with data
int current_index = 0;        // Keeps track of data being sent

void setup() {
    Wire.begin(SLAVE_ADDRESS);
    Wire.onRequest(requestEvent); // Register the request handler
    Serial.begin(9600);

    // Initialize data_array with example values
    


    Serial.println("I2C Slave Ready");
}

void loop() {
    // Main loop does nothing; data is sent on request
}

void requestEvent() {
    byte chunk[CHUNK_SIZE]; // Temporary buffer for sending data
    int chunk_index = 0;

    while (chunk_index < CHUNK_SIZE && current_index < ROWS * COLS) {
        // Convert current float to bytes
        byte* float_bytes = (byte*)&data_array[current_index / COLS][current_index % COLS];

        // Add float bytes to the chunk
        for (int i = 0; i < FLOAT_SIZE; i++) {
            chunk[chunk_index++] = float_bytes[i];
            if (chunk_index >= CHUNK_SIZE) break;
        }

        current_index++; // Move to next float
    }

    // If the chunk is not completely filled, pad with zeros
    while (chunk_index < CHUNK_SIZE) {
        chunk[chunk_index++] = 0;
    }

    // Send the chunk
    Wire.write(chunk, CHUNK_SIZE);

    // Reset the index after the entire array is sent
    if (current_index >= ROWS * COLS) {
        current_index = 0;
    }
}
