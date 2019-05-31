#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	loadSetting();

	video.load("back.mp4");
	video.setLoopState(OF_LOOP_NORMAL);
	video.setVolume(volume);
	video.play();
	isMute = false;

	{
		listener.Create();
		listener.SetNonBlocking(true);
		listener.Bind(port);
	}
	ofSetWindowTitle("backMusicV1.0");
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
	video.update();


	char data[100];

	listener.Receive(data, 100);
	string msg = data;
	if ("" != msg)
	{
		if (muteCmd == msg)
		{
			video.setVolume(volume * 0.2f);
			isMute = true;
		}
		else if (unmuteCmd == msg)
		{
			video.setVolume(volume * 1.0f);
			isMute = false;
		}
		else if (volumeAddCmd == msg)
		{
			volume += 0.1f;
			volume = ofClamp(volume, 0.0f, 1.0f);
			video.setVolume(volume);

			saveSetting();
		}
		else if (volumeSubCmd == msg)
		{
			volume -= 0.1f;
			volume = ofClamp(volume, 0.0f, 1.0f);
			video.setVolume(volume);

			saveSetting();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	video.draw(0,0,ofGetWidth(),ofGetHeight());
	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofDrawBitmapString("volume:" + ofToString(volume), 20, 20);
	isMute ? ofSetColor(0, 255, 0) : ofSetColor(0, 0, 255);
	string msg = "";
	isMute ? msg = "mute" : msg = "unmute";
	ofDrawBitmapString(msg, 20, 40);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit()
{
	video.close();
}

void ofApp::loadSetting()
{
	{
		ofxXmlSettings xml;
		xml.load("config.xml");
		port = xml.getValue("port", 16999);
		muteCmd = xml.getValue("cmd_mute", "music_mute");
		volumeAddCmd = xml.getValue("cmd_volume_add", "music_add");
		volumeSubCmd = xml.getValue("cmd_volume_sub", "music_sub");
		unmuteCmd = xml.getValue("cmd_unmute", "music_unmute");
	}

	{
		ofxXmlSettings xml;
		xml.load("volume.xml");
		volume = xml.getValue("volume", 1.0f);
	}
}

void ofApp::saveSetting()
{
	ofxXmlSettings xml;
	
	xml.addValue("volume", volume);

	xml.save("volume.xml");
}