[V1.1](https://github.com/uhpowerup/ESP32-KISS-TNC/releases/tag/V1.1) is out.
# ESP32-KISS-TNC
Simple KISS TNC bases on ESP32
There are many KISS TNCs available online, both commercially and as DIY projects. While most DIY options offer high-quality hardware, they often lack one critical component—open-source firmware. Many projects provide only the HEX file for pre-programmed microcontrollers, limiting the ability to modify or understand the underlying code.  
This led me to embark on my own KISS TNC project, inspired by the work of [KV4P](https://kv4p.com/quick_start.html). I replicated his audio interface for APRS, but when it came to the firmware, I wanted a fully customizable solution.  
To kickstart the development, I experimented with AI-generated code. I provided [OpenAI](https://chatgpt.com/) with my project details, including the ESP32 pinout, and asked for a simple KISS TNC implementation. The initial results were promising but required further refinement. Through multiple iterations, I improved the code to better align with the project’s needs.  
To build  KISS TNC, you’ll need a few essential components. This project is based on the ESP32 WROOM Dev Kit v4 and a simple audio interface for APRS. Here’s what you’ll need:  

**Required Components:**
- **ESP32 WROOM Dev Kit v4** – The heart of the TNC, handling signal processing and communication.  
- **2x 10nF Ceramic Capacitors** – Used for signal filtering.  
- **1x 1K Resistor** – Part of the circuit to ensure proper signal levels.  
- **3x 10K Resistors** – Used for pull-up and pull-down configurations.  
- **1x NPN Transistor (BC547 or 2N2222)** – Used for PTT (Push-To-Talk) control.  
- **I/O Plug (Minimum 4 Pins)** – For interfacing with your radio.  

This setup provides a simple yet effective way to decode and transmit APRS signals using the ESP32.

73's

[2E0UMR](2e0umr.me)

