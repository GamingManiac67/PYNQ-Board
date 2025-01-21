#include <Wire.h>

#define SLAVE_ADDRESS 0x08
#define ROWS 2       // Number of rows in the 2D array
#define COLS 2     // Number of columns in the 2D array
#define CHUNK_SIZE 32 // Number of bytes received per chunk
#define FLOAT_SIZE 4  // Size of a float in bytes

float data_array[ROWS][COLS]; // Array to store the received floats
byte buffer[CHUNK_SIZE];      // Temporary buffer for receiving data
int received_floats = 0;      // Total number of floats received

void setup() {
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveEvent);
    Serial.begin(9600);
    Serial.println("I2C Slave Ready");
}

void loop() {
    // Check if all data is received
    if (received_floats == ROWS * COLS) {
        Serial.println("Full data received. Printing array:");

        // Print the received array in proper C++ format
        Serial.println("{");
        for (int i = 0; i < ROWS; i++) {
            Serial.print("  {");
            for (int j = 0; j < COLS; j++) {
                Serial.print(data_array[i][j], 6); // Print with 6 decimal places
                if (j < COLS - 1) Serial.print(", "); // Add a comma between elements
            }
            Serial.print("}");
            if (i < ROWS - 1) Serial.println(","); // Add a comma between rows
        }
        Serial.println("\n};");

        // Reset for next transmission
        received_floats = 0;
    }
}

// Function to handle data received via I2C
void receiveEvent(int bytes) {
    static int buffer_index = 0; // Keeps track of where to store the next float

    while (Wire.available() > 0 && buffer_index < CHUNK_SIZE) {
        buffer[buffer_index++] = Wire.read(); // Read byte into buffer
    }

    // Process the buffer once full or if no more bytes available
    if (buffer_index == CHUNK_SIZE || Wire.available() == 0) {
        // Convert bytes to floats and store them in the array
        for (int i = 0; i < buffer_index; i += FLOAT_SIZE) {
            if (received_floats < ROWS * COLS) {
                int row = received_floats / COLS;
                int col = received_floats % COLS;

                // Reconstruct the float from 4 bytes
                float value;
                memcpy(&value, &buffer[i], FLOAT_SIZE);
                data_array[row][col] = value;

                received_floats++; // Increment received float count
            }
        }
        buffer_index = 0; // Reset buffer index for next chunk
    }
}
