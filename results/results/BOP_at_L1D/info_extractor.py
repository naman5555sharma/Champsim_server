import re
import os
import csv

# Function to extract information from log text
def extract_info(log_text):
    result = {}
    
    # Extracting IPC
    ipc_match = re.search(r'CPU 0 cumulative IPC: (\d+\.\d+)', log_text)
    if ipc_match:
        ipc = ipc_match.group(1)
        result['IPC'] = ipc
    
    # Extracting MPKI for ITLB, DTLB, STLB, LLC
    areas = ['L2C TOTAL','L1I TOTAL','L1D TOTAL','ITLB TOTAL', 'DTLB TOTAL', 'STLB TOTAL', 'LLC TOTAL']
    for area in areas:
        mpki_match = re.search(rf'{area}.*?MPKI:\s(\d+\.\d+)', log_text, re.DOTALL)
        if mpki_match:
            mpki = mpki_match.group(1)
            result[f"{area}_MPKI"] = mpki
    
    # Extracting L1D accuracy
    l1d_accuracy_match = re.search(r'L1D USEFUL LOAD PREFETCHES:.*?ACCURACY:\s*([\d.-]+)', log_text, re.DOTALL)
    if l1d_accuracy_match:
        l1d_accuracy = l1d_accuracy_match.group(1)
        result['L1D Accuracy'] = l1d_accuracy
    
    # Extracting L2C accuracy
    l2c_accuracy_match = re.search(r'L2C USEFUL LOAD PREFETCHES:.*?ACCURACY:\s*([\d.-]+)', log_text, re.DOTALL)
    if l2c_accuracy_match:
        l2c_accuracy = l2c_accuracy_match.group(1)
        result['L2C Accuracy'] = l2c_accuracy
    
    # Extracting LLC accuracy
    llc_accuracy_match = re.search(r'LLC USEFUL LOAD PREFETCHES:.*?ACCURACY:\s*([\d.-]+)', log_text, re.DOTALL)
    if llc_accuracy_match:
        llc_accuracy = llc_accuracy_match.group(1)
        result['LLC Accuracy'] = llc_accuracy
    
    return result

# Directory containing log files
folder_path = '.'  # Replace 'folder_with_logs' with your folder containing logs

# List all files in the directory
files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]

# Process each file
output_data = []
for file_name in files:
    file_path = os.path.join(folder_path, file_name)
    with open(file_path, 'r', encoding='latin-1') as file:
        log_text = file.read()
        info = extract_info(log_text)
        info['File'] = file_name  # Add file name to the result
        output_data.append(info)

# Writing to CSV
output_file = 'output.csv'  # Name of the output CSV file
keys = output_data[0].keys() if output_data else []  # Get the keys if data exists

with open(output_file, 'w', newline='') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=keys)
    writer.writeheader()
    writer.writerows(output_data)

