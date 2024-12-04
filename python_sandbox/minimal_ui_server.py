from flask import Flask, render_template, request

app = Flask(__name__, template_folder="../smart_ir_bridge/templates")

# Mock scan results
MOCK_SCAN_RESULTS = [
    "Sample Network 1 (-50 dBm)",
    "Sample Network 2 (-60 dBm)",
    "Sample Network 3 (-70 dBm)"
]

@app.route("/", methods=["GET"])
def index():
    # Step/tab 1: Wi-Fi Connection
    return render_template("index.html", active_tab="step1", display="none", scan_results=[])

@app.route("/scan", methods=["POST"])
def scan():
    # Simulate Wi-Fi scan and return results
    scan_results = MOCK_SCAN_RESULTS  # Simulate Wi-Fi scan results
    return render_template("index.html", active_tab="step1", display="block", scan_results=scan_results)

@app.route("/connect", methods=["POST"])
def connect():
    # Simulate Wi-Fi connection logic
    ssid = request.form.get('ssid')
    password = request.form.get('password')
    # Simulate connection attempt
    print(f"Attempting to connect to SSID: {ssid} with password: {password}")
    # Return a response or redirect
    return f"Attempting to connect to SSID: {ssid}"

@app.route("/mqtt", methods=["GET"])
def mqtt():
    # Step/tab 2: MQTT Server Connection
    return render_template("index.html", active_tab="step2")

@app.route("/mqtt-save", methods=["POST"])
def mqtt_save():
    # Get MQTT settings from the form
    mqtt_broker = request.form.get('mqtt_broker')
    mqtt_port = request.form.get('mqtt_port')
    mqtt_username = request.form.get('mqtt_username')
    mqtt_password = request.form.get('mqtt_password')
    # Simulate saving the settings (not checking validity)
    print(f"MQTT Broker: {mqtt_broker}")
    print(f"MQTT Port: {mqtt_port}")
    print(f"MQTT Username: {mqtt_username}")
    print(f"MQTT Password: {mqtt_password}")
    # Return a response or redirect
    return "MQTT Settings Saved Successfully"

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)
