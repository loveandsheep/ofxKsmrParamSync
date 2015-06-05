//
//  paramSyncTemplate.h
//  SignageViewer
//
//  Created by Ovis aries on 2015/02/19.
//
//
//ofParameterと変数のポインタをバインドできる（アプリ間の値同期等で便利なテンプレートクラス）

#ifndef __SignageViewer__paramSyncTemplate__
#define __SignageViewer__paramSyncTemplate__

#include "ofMain.h"

class paramSyncTempBase{
public:

	virtual void refleshFromParamGroup(ofParameterGroup &grp){}
	virtual void upStreamFromParam(ofParameterGroup &grp){}

};

template <typename T> class paramSyncTemplate : public paramSyncTempBase{
public:

	paramSyncTemplate(){};
	~paramSyncTemplate(){};

	void setup(string paramName, T* paramPtr){
		pName = paramName;
		pPtr = paramPtr;
	}

	virtual void refleshFromParamGroup(ofParameterGroup &grp){
		*pPtr = grp.get<T>(pName);
	}

	virtual void upStreamFromParam(ofParameterGroup &grp){
		grp.get<T>(pName) = *pPtr;
	}

	string	pName;
	T*		pPtr;

};

class abstractParamContainer{
public:

	template<typename T> void addNewParams(string name, T *pt, ofParameterGroup& grp){

		ofPtr<paramSyncTemplate<T> > prm;
		prm = ofPtr<paramSyncTemplate<T> >(new paramSyncTemplate<T>);
		prm->setup(name, pt);

		grp.add((* new ofParameter<T>(name, *pt)));
		params.push_back(prm);
		
	}

	
	void refleshParams(ofParameterGroup &grp){

		for (int i = 0;i < params.size();i++){
			params[i]->refleshFromParamGroup(grp);
		}
		
	}

	void upStreamFromParam(ofParameterGroup &grp){

		for (int i = 0;i < params.size();i++){
			params[i]->upStreamFromParam(grp);
		}

	}

	vector<ofPtr<paramSyncTempBase> > params;
};

#endif /* defined(__SignageViewer__paramSyncTemplate__) */

