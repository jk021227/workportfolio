"""Does tests for ze program"""
import os
import pytest
import json
import base64
from dotenv import load_dotenv
from src.main import detect_encoding, get_image
from src.web_app import connect_to_db, app, get_emotion_aggregate
from unittest.mock import patch, MagicMock

load_dotenv()
DATABASE_CONNECTION_STRING = os.getenv("DATABASE_CONNECTION_STRING")

def database_connection_string():
    """DB connection string"""
    return DATABASE_CONNECTION_STRING


def test_connection_to_db_successful():
    """Tests connection to DB"""
    ml_data, database = connect_to_db(database_connection_string())
    assert ml_data is not None
    assert database is not None


def test_collection_and_database_exist():
    """Tests db connection and existence"""
    ml_data, database = connect_to_db(database_connection_string())
    assert ml_data.name == "DataForMachineLearning"
    assert database.name == "MLData"


def test_detect_encoding1():
    """Tests detect encoding 1"""
    file_path = "tst/test_web_app/tests/testFile1.txt"
    detect_encoding(file_path)


def test_detect_encoding2():
    """Tests detect encoding 2"""
    detect_encoding("tst/test_web_app/tests/testFile1.txt")


def test_detect_encoding3():
    """Tests detect encoding 3"""
    file_path = "tst/test_web_app/tests/testFile1.txt"
    detect_encoding(file_path)
    detect_encoding("tst/test_web_app/tests/testFile1.txt")


def test_get_image():
    """Test if get_image function returns a valid file path."""
    image_path = get_image()
    assert os.path.exists(image_path)
    assert os.path.isfile(image_path)


@pytest.fixture
def client():
    app.config["TESTING"] = True
    with app.test_client() as client:
        yield client


def test_about_route(client):
    """Test the about GET route."""
    response = client.get("/about")
    assert response.status_code == 200
    assert b"Make sure" in response.data


def test_data_collection_get_route(client):
    """Test the data collection GET route."""
    response = client.get("/data_collection")
    assert response.status_code == 200
    assert b"Capture" in response.data


def test_data_collection_post_route(client):
    """Test the data collection POST route."""
    image_data = base64.b64encode(b"Test Image Data").decode("utf-8")
    response = client.post(
        "/data_collection", json={"image": f"data:image/png;base64,{image_data}"}
    )
    assert response.status_code == 200
    data = json.loads(response.data)
    assert "Image uploaded successfully" in data["message"]


def test_get_emotion_aggregate():
    with patch("src.web_app.connect_to_db") as mock_connect_to_db:
        # mocking database query
        mock_collection = MagicMock()
        mock_collection.find.return_value = [
            {"emotion": "happy"},
            {"emotion": "sad"},
            {"emotion": "happy"},
        ]
        mock_connect_to_db.return_value = (mock_collection, None)
        emotion_data = get_emotion_aggregate()
        assert emotion_data == {"happy": 2, "sad": 1}
