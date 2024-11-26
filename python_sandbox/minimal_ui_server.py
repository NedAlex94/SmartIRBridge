# minimal_ui_server.py

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
    return render_template("index.html", scan_results=None)

@app.route("/scan", methods=["POST"])
def scan():
    scan_results = MOCK_SCAN_RESULTS  # Simulate Wi-Fi scan results
    return render_template("index.html", scan_results=scan_results)

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)
