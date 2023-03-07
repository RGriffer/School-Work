FROM python:latest
#ADD server.py /server/app/
WORKDIR /server/
COPY app/server.py .
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt
ENV FLASK_APP=server.py
COPY . .
CMD ["python", "server.py", "9"]