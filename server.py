from flask import Flask, request, jsonify

server_data = Flask(__name__)

@server_data.route("/")
def welcome():
    return "You are connected!"

@server_data.route("/sensor-data", methods=["POST"])
def post_data():
    data = request.get_json()
    print(f"Successfully Received Data: {data}")

    return jsonify({"Message": "Data Received Successfully"}), 200

if __name__ == "__main__":
    server_data.run(debug=True, host="127.0.0.1", port=5000)