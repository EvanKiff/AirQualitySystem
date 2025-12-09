import folium
import pandas as pd
import numpy as np
from math import radians, sin, cos, sqrt, atan2

# ---------------------------------------------------
# Load data from .txt file
df = pd.read_csv(
    "data.txt",
    header=None,
    names=[
        "lat", "lon", "alt", "co2", "temp", "humidity",
        "pm1", "pm25", "pm10"
    ]
)

# Haversine distance (meters)
def haversine_m(lat1, lon1, lat2, lon2):
    R = 6371000  # Earth radius in meters
    phi1, phi2 = radians(lat1), radians(lat2)
    dphi = radians(lat2 - lat1)
    dlambda = radians(lon2 - lon1)

    a = sin(dphi/2)**2 + cos(phi1) * cos(phi2) * sin(dlambda/2)**2
    return 2 * R * atan2(sqrt(a), sqrt(1 - a))


# Cluster points within 100 ft (~30.48 m)
MAX_DIST = 30.48

clusters = []
visited = set()

for i in range(len(df)):
    if i in visited:
        continue

    # Start a new cluster with point i
    cluster_points = [i]
    visited.add(i)

    lat1, lon1 = df.loc[i, "lat"], df.loc[i, "lon"]

    # Compare with all other points
    for j in range(i + 1, len(df)):
        if j in visited:
            continue

        lat2, lon2 = df.loc[j, "lat"], df.loc[j, "lon"]
        d = haversine_m(lat1, lon1, lat2, lon2)

        if d <= MAX_DIST:
            cluster_points.append(j)
            visited.add(j)

    clusters.append(cluster_points)

# Average all clusters into single points
averaged_rows = []

for cluster in clusters:
    subset = df.loc[cluster]

    avg_row = {
        "lat": subset["lat"].mean(),
        "lon": subset["lon"].mean(),
        "alt": subset["alt"].mean(),
        "co2": subset["co2"].mean(),
        "temp": subset["temp"].mean(),
        "humidity": subset["humidity"].mean(),
        "pm1": subset["pm1"].mean(),
        "pm25": subset["pm25"].mean(),
        "pm10": subset["pm10"].mean(),
        "count": len(subset)  # for debugging
    }

    averaged_rows.append(avg_row)

df_avg = pd.DataFrame(averaged_rows)

print(f"Averaged {len(df)} points down to {len(df_avg)} spatial clusters.")

# Marker color logic (CO₂ + PM2.5)
def get_color(row):
    pm = row["pm25"]
    co2 = row["co2"]

    # PM2.5 takes priority — directly harmful
    if pm > 150:
        return "darkred"   # dangerous PM
    if pm > 55:
        return "red"       # unhealthy
    if pm > 15:
        return "orange"    # moderate

    # CO2 thresholds after PM
    if co2 > 2000:
        return "purple"    # very high CO2
    if co2 > 1500:
        return "magenta"   # high CO2
    if co2 > 1000:
        return "blue"      # elevated CO2

    return "green"         # good air quality

# Create Folium Map
center_lat = df_avg["lat"].mean()
center_lon = df_avg["lon"].mean()

m = folium.Map(location=[center_lat, center_lon], zoom_start=15)

# Add averaged markers to map
for _, row in df_avg.iterrows():

    color = get_color(row)

    popup_html = f"""
    <b>Sensor Reading (Averaged)</b><br>
    Avg of {row['count']} samples<br><br>

    <b>Location</b><br>
    Lat: {row['lat']}<br>
    Lon: {row['lon']}<br>
    Alt: {row['alt']:.1f} m<br><br>

    <b>Environmental</b><br>
    Temp: {row['temp']:.2f} °C<br>
    Humidity: {row['humidity']:.2f}%<br>
    CO₂: {row['co2']:.2f} ppm<br><br>

    <b>Particles</b><br>
    PM1.0: {row['pm1']:.2f} µg/m³<br>
    PM2.5: {row['pm25']:.2f} µg/m³<br>
    PM10: {row['pm10']:.2f} µg/m³<br>
    """

    folium.CircleMarker(
        location=[row["lat"], row["lon"]],
        radius=7,
        color=color,
        fill=True,
        fill_color=color,
        fill_opacity=0.9,
        popup=popup_html
    ).add_to(m)


# ---------------------------------------------------
# Save output
# ---------------------------------------------------
m.save("environment_map.html")
print("SUCCESS: Map saved as environment_map.html")
