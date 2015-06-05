//
//  ofxKsmrParamSync.cpp
//  SignageViewer
//
//  Created by Ovis aries on 2015/02/12.
//
//

#include "ofxKsmrParamSync.h"

void ofxKsmrParamSync::setup(string syncId,ofxKsmrOscDistributor *dst, string externalPath){

	idAddress = syncId;
	receiver = ofPtr<ofxKsmrOscTip>(new ofxKsmrOscTip);
	receiver->addAddress("/ksmr/param/"+idAddress);
	dst->addReceiverTag(receiver);

	currentPort = dst->currentPort;
	paramRW.setGroup(&params);
	extPath = externalPath;
}

void ofxKsmrParamSync::update(){

	while (receiver->hasWaitingMessages()){

		ofxOscMessage m;
		receiver->getNextMessage(&m);

		string myId = "/ksmr/param/"+idAddress;

		if (m.getAddress() == myId + "/sync"){
			catchSerialized(m.getArgAsString(0), m.getArgAsInt32(1) == 1);
		}

		if (m.getAddress() == myId + "/request"){
			ofXml xml;
			paramRW.saveTo(xml);
			ofxOscMessage Rt;
			Rt.setAddress(myId + "/sync");
			Rt.addStringArg(xml.toString());

			ofxOscSender s;
			s.setup(m.getRemoteIp(), m.getArgAsInt32(0));
			s.sendMessage(Rt);
		}
		
	}

}

void ofxKsmrParamSync::sendRequest(string address, int port){
	ofxOscSender sender;
	sender.setup(address, port);

	ofxOscMessage m;
	m.setAddress("/ksmr/param/" + idAddress + "/request");
	m.addIntArg(currentPort);

	sender.sendMessage(m);
}

void ofxKsmrParamSync::sendSerialized(string address, int port, bool withSave){

	ofXml xml;

	paramRW.saveTo(xml);
	if (withSave) save();

	ofxOscSender sender;
	sender.setup(address, port);

	ofxOscMessage m;
	m.setAddress("/ksmr/param/" + idAddress + "/sync");
	m.addStringArg(xml.toString());
	m.addIntArg(withSave ? 1 : 0);
	
	sender.sendMessage(m);
}

void ofxKsmrParamSync::catchSerialized(string serialized, bool withSave){

	ofXml xml;
	xml.loadFromBuffer(serialized);

	paramRW.loadFrom(xml);
	if (withSave) save();

	isNewValue = true;
}

bool ofxKsmrParamSync::getIsNewValue(){

	bool ret = isNewValue;

	isNewValue = false;

	return ret;

}

void ofxKsmrParamSync::save(){
	paramRW.save(extPath + "settings/params_" + idAddress + ".xml");
}

bool ofxKsmrParamSync::load(){
	if (ofDirectory::doesDirectoryExist(extPath + "settings/params_" + idAddress + ".xml")){
		paramRW.load(extPath + "settings/params_" + idAddress + ".xml");
		return true;
	}else {
		return false;
	}
}