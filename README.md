# ESP32 GPS Data Visualization with MQTT and Python

This project demonstrates how to send GPS data from an ESP32 to a Python server using the MQTT protocol and visualize the data using a Streamlit web application.

## Prerequisites

Before you can start with this project, make sure you have the following components and software installed:

- ESP32 microcontroller with WiFi capabilities
- GPS module connected to the ESP32
- A computer with Python and pip installed
- A stable internet connection

## Getting Started

1. **Setup ESP32:**
    - Open the Arduino IDE or platform of your choice for programming the ESP32.
    - Update the WiFi SSID and password in your ESP32 code.
    - Upload the code to the ESP32. This code should collect GPS data and send it to your MQTT broker.

2. **Python Server:**
    - Make sure you have Python 3.x installed.
    - Create a virtual environment if desired:
        ```bash
        python -m venv venv
        source venv/bin/activate  # On Windows, use venv\Scripts\activate
        ```
    - Install the required Python packages using pip:
        ```bash
        pip install -r requirements.txt
        ```

3. **MQTT Broker:**
    - You can set up a local MQTT broker or use a cloud-based service.
    - Ensure that the ESP32 code is configured to connect to the MQTT broker.


4. **Streamlit Web Application:**
    - Start the Streamlit web application to visualize the GPS data.
    ```bash
    streamlit run main.py
    ```

5. **Access the Web App:**
    - Open a web browser and navigate to the Streamlit application's URL (usually http://localhost:8501).

## Project Structure

- `esp.ino/`: Contains the code to run on the ESP32.
- `main.py/`: Contains Python scripts to collect and visualize GPS data.
- `requirements.txt`: Lists the Python package dependencies.

## Additional Configuration

- MQTT Broker Configuration: You may need to configure the MQTT broker details (e.g., server address, port) in both the ESP32 code and `gps_listener.py`.
- Customize the Streamlit Application: Modify `gps_visualizer.py` to customize the web application's appearance and behavior.


## Acknowledgments

- [Streamlit](https://streamlit.io/)
- [MQTT](https://mqtt.org/)
- [ESP32](https://www.espressif.com/en/products/socs/esp32)
- Your GPS module manufacturer's documentation

## Author

[Shukur Alam]

