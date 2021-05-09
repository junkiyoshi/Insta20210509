#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);


}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	auto len = 150;
	auto log = 315;
	auto param = 60;

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	for (int i = 0; i <= log; i++) {

		int face_index = this->face.getNumVertices();
		int line_index = this->line.getNumVertices();

		auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i) * -0.0035), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
		auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i) * -0.0035), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
		auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed.z, (ofGetFrameNum() + i) * -0.0035), 0, 1, -PI, PI), glm::vec3(0, 0, 1));

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec4(param, param, param, 0) * rotation_z * rotation_y * rotation_z);
		vertices.push_back(glm::vec4(param, -param, -param, 0) * rotation_z * rotation_y * rotation_z);
		vertices.push_back(glm::vec4(-param, param, -param, 0) * rotation_z * rotation_y * rotation_z);
		vertices.push_back(glm::vec4(-param, -param, param, 0) * rotation_z * rotation_y * rotation_z);

		int deg = i + ofGetFrameNum();
		auto base_location = glm::vec3(
			500 * cos(deg * DEG_TO_RAD),
			500 * sin(deg * DEG_TO_RAD),
			0);

		for (auto& vertex : vertices) {

			vertex = base_location + glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
		}

		this->line.addVertices(vertices);

		if (i % 45 == 0 || i == log) {

			this->face.addVertices(vertices);

			this->face.addIndex(0); this->face.addIndex(1); this->face.addIndex(2);
			this->face.addIndex(0); this->face.addIndex(1); this->face.addIndex(3);
			this->face.addIndex(0); this->face.addIndex(2); this->face.addIndex(3);
			this->face.addIndex(1); this->face.addIndex(2); this->face.addIndex(3);

			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 2);
			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 3);
			this->face.addIndex(face_index + 0); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 3);
			this->face.addIndex(face_index + 1); this->face.addIndex(face_index + 2); this->face.addIndex(face_index + 3);

		}
		else {

			if (line_index > 0 && i > 0) {

				this->line.addIndex(line_index - 4); this->line.addIndex(line_index + 4);
				this->line.addIndex(line_index - 3); this->line.addIndex(line_index + 5);
				this->line.addIndex(line_index - 2); this->line.addIndex(line_index + 6);
				this->line.addIndex(line_index - 1); this->line.addIndex(line_index + 7);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	ofSetLineWidth(2);
	this->face.drawWireframe();

	ofSetColor(39);
	ofSetLineWidth(1);
	this->line.draw();

	for (int i = 0; i < this->face.getNumVertices(); i++) {

		ofDrawSphere(this->face.getVertex(i), 10);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}