# Perform data analysis on parsed data
import LineParser
import pandas as pd
def main(filename="sensor_data.txt"):
    """
    Main function to read and parse the sensor data file.
    """
    parsed_data = []
    try:
        with open(filename, 'r') as f:
            for line in f:
                if not line.strip():  # Skip empty lines
                    continue

                data_point = LineParser.parse_sensor_line(line)

                if data_point:
                    parsed_data.append(data_point)

    except FileNotFoundError:
        print(f"Error: The file '{filename}' was not found.")
        return
    except Exception as e:
        print(f"An error occurred while reading the file: {e}")
        return

    if parsed_data:
        print(f"Successfully parsed {len(parsed_data)} data points.")
        df = pd.DataFrame(parsed_data)
        print("\nSensor Data as DataFrame:")
        print(df)
    else:
        print("No valid data was parsed.")

if __name__ == "__main__":
    # You can change the filename here or pass it as a command-line argument
    main(filename="test.txt")