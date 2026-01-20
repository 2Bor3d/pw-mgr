import flask

app = flask.Flask(__name__);


@app.route("/")
def index():
    with open("test.html") as index:
        return index.read();


@app.route("/test.js")
def js():
    with open("test.js") as js:
        return js.read();


@app.route("/test.wasm")
def wasm():
    wasm = open("test.wasm", "rb");

    return flask.send_file(
            wasm,
            mimetype='application/wasm')


if __name__ == "__main__":
    app.run();

