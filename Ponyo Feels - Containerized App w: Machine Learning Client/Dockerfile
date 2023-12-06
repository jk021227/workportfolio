FROM python:3.9-alpine


WORKDIR /

ENV FLASK_APP=app.py
ENV FLASK_RUN_HOST=0.0.0.0
# ENV DATABASE_CONNECTION_STRING = DATABASE_CONNECTION_STRING


RUN apk add --no-cache gcc musl-dev linux-headers
COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt


EXPOSE 5001
COPY . .
# RUN coverage run -m pytest
#RUN pylint src/*.py
RUN pytest tst
WORKDIR /
CMD ["python3", "-m", "src.web_app"]

#! Make sure that all containers can comm with each other.