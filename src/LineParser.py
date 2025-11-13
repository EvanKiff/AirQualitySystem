# Parse lines of data
def parse_sensor_line(line):
    """
    # Format: latitude, longitude, altitude, temp, humidity, co2, pm1.0, pm2.5, pm10.0
    """
    parts = line.split(',')
    parts = [p.strip() for p in parts]
    if len(parts) != 9:
        print(f"Warning: Skipping malformed line: {line.strip()}")
        return None
    try:
        data = {
            'Latitude': float(parts[0]),
            'Longitude': float(parts[1]),
            'Altitude': float(parts[2]),
            'Temperature ($\circ C$)': float(parts[3]),
            'Humidity (%)': float(parts[4]),
            'CO2 Concentration (ppm)': float(parts[5]),
            'PM 1.0 Concentration ($\mu g/m^3$)': float(parts[6]),
            'PM 2.5 Concentration ($\mu g/m^3$)': float(parts[7]),
            'PM 10.0 Concentration ($\mu g/m^3$)': float(parts[8])
        }
        return data
    except ValueError:
        print(f"Warning: Skipping line with non-numeric data: {line.strip()}")
        return None
    except Exception as e:
        print(f"An unexpected error occurred on line: {line.strip()} - {e}")
        return None