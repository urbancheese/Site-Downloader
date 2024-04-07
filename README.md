# Malware Downloader

## Overview

This program is designed to download a malware file from a specified URL, add it to the Windows Defender exclusions list, execute the downloaded file, and then re-enable Windows Defender's real-time protection.

## Usage

1. Ensure that you have administrative privileges to run the program.
2. Compile and run the program.
3. Follow the on-screen instructions if any.

## Installation

- Clone this repository to your local machine.
- Compile the source code using a C++ compiler.
- Run the compiled executable with administrative privileges.

## What It Does

- Downloads a malware file from a specified URL.
- Adds the downloaded malware file to the Windows Defender exclusions list to prevent it from being scanned.
- Executes the downloaded malware file.
- Re-enables Windows Defender's real-time protection after executing the malware.

## Requirements

- Windows operating system.
- Administrative privileges to run the program.
- C++ compiler for compiling the source code.

## Obfuscated Variable Names Explanation

- **U**: Represents the URL from which the malware file will be downloaded. It's set to "https://example.com/virus.exe".
  
- **V**: Stands for the name of the downloaded malware file. It's set to "virus.exe".

- **W**: Represents the path where the downloaded malware file will be saved on the local system. It's set to "D:\\security\\virus.exe".

- **X**: Denotes the chunk size used for downloading the malware file. It determines how much data is fetched in each network request. It's set to 524288 bytes (or approximately 512 KB).

