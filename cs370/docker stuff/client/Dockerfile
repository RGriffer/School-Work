FROM python:latest
#ADD client.py /client/app/
WORKDIR /client/
COPY app/client.py .
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt
COPY . .
CMD ["python", "client.py"]