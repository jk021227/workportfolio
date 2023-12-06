"""All necessary imports to run web_app.py"""
import os
import asyncio
import logging
import base64
import pymongo
from dotenv import load_dotenv
from flask import Flask, render_template, request, jsonify
from .main import main


logging.basicConfig(level=logging.INFO)
load_dotenv()
DATABASE_CONNECTION_STRING = os.getenv("DATABASE_CONNECTION_STRING")
log = logging.getLogger()
app = Flask(__name__)
app.secret_key = "no body no crime"


def connect_to_db(connection_string):
    """Connects to DB"""
    try:
        client = pymongo.MongoClient(connection_string)
        database = client.MLData
        ml_data = database.get_collection("DataForMachineLearning")
        return ml_data, database
    except ConnectionError as error:
        logging.error("Exception connecting to MongoDB: %s", error)
        raise


log = logging.getLogger()
ml_collection = connect_to_db(DATABASE_CONNECTION_STRING)


@app.route("/")
def view_dashboard():
    """renders dashboard"""
    return render_template("homepage.html")


@app.route("/data_collection", methods=["GET"])
def data_collection_get():
    """gets page for data collection"""
    return render_template("data_collection.html")


@app.route("/data_collection", methods=["POST"])
def data_collection_post():
    """handles post request of photo that was collected on page"""
    try:
        image_data = request.json["image"]  # extracting base64 image data
        image_binary = base64.b64decode(image_data.split(",")[1])  # decode the image

        # determining file path
        script_dir = os.path.dirname(__file__)  # directory of the script
        target_dir = os.path.join(
            script_dir, "..", "images"
        )  # navigating up 'images' folder

        # defining file name, it doesn't need to be unique if docker file clears image folder
        file_path = os.path.join(target_dir, "uploaded_image.png")

        # writing image data into a file
        with open(file_path, "wb") as file:
            file.write(image_binary)
        # return redirect(url_for('return_emotion'))

        return jsonify(
            {"message": "Image uploaded successfully", "file_path": file_path}
        )

    except ConnectionError as error:
        logging.error("Error uploading image: %s", error)
        return jsonify({"error": "Error uploading image"}), 500


@app.route("/data_output", methods=["GET"])
def return_emotion():
    """returns emotion to the output page"""
    emotion = get_emotion()
    db_emotion_list = get_emotion_aggregate()

    return render_template(
        "data_output.html", emotion=emotion, emotions_data=db_emotion_list
    )


@app.route("/about", methods=["GET"])
def view_about():
    """View page."""
    return render_template("about.html")


@app.route("/homepage", methods=["GET"])
def view_homepage():
    """Homepage"""
    return render_template("homepage.html")


def get_emotion():
    """Get the current emotion using the main function."""
    result = asyncio.run(main())
    emotion = result[0]
    emotion_dic = {"emotion": emotion}
    ml_lib, _ = connect_to_db(DATABASE_CONNECTION_STRING)
    ml_lib.insert_one(emotion_dic)
    return emotion


def get_emotion_aggregate():
    """Aggregate emotion data from the database."""
    ml_lib, _ = connect_to_db(DATABASE_CONNECTION_STRING)
    db_emotion_list = {}
    for doc in ml_lib.find():
        emote = doc.get("emotion")
        if emote in db_emotion_list:
            db_emotion_list[emote] += 1
        else:
            if emote is not None:
                db_emotion_list[emote] = 1
    return db_emotion_list


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5001)
