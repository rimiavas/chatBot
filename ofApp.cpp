#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(50);
    textParameter.addListener(this, &ofApp::onTextChange);
    
    parameters.setName("Text input");
    parameters.add(textParameter.set("", ""));
    gui.setDefaultWidth(300);
    gui.setup(parameters);
    
    gui.setPosition(10,10);
    lineHeight = 20;
    
    messageBuffer.push_front("bot>> Hello. what seems to be the problem?");
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //No need to add anything to draw
    gui.draw();
    
    for(int i = 0; i < messageBuffer.size(); i++){
        ofDrawBitmapString(messageBuffer[i], 10, 70 + lineHeight * i);
    }
        
        //pop back messages once there are more than can be displayed
    float messagePxHeight = messageBuffer.size() * lineHeight + 70;
    if(messagePxHeight > ofGetHeight()){
        messageBuffer.pop_back();
    }
    
}

void ofApp::parrotBot(string inputText){
 
    //Ther's not much going on in the parrotBot
    phrases.push_back(inputText);
    int index = ofRandom(phrases.size());
    string phrase = phrases[index];
    
    //add your input to the messageBuffer
    messageBuffer.push_front("parrotBot>> " + inputText);
    
}

void ofApp::phraseBot(string inputText) {

    //Ther's not much going on in the phraseBot
    phrases.push_back(inputText);
    int index = ofRandom(phrases.size());
    string phrase = phrases[index];

    //add your input to the messageBuffer
    messageBuffer.push_front("phraseBot>> " + phrase);

}

void ofApp::mangleBot(string inputText) {

    //Ther's not much going on in the mangleBot
    vector<string>temporaryStrings;
    temporaryStrings = tokenise(inputText, ' ');
    for (string word : temporaryStrings) {
        words.push_back(word);
    }
    string output;
    for (int i = 0; i < 5; i++) {
        int index = ofRandom(words.size());
        output += words[index] + " ";
    }
    //add your input to the messageBuffer
    messageBuffer.push_front("mangleBot>> " + output);

}

void ofApp::markovBot(string inputText) {

    //Ther's not much going on in the markovBot
    wordChain = addWordsToMarkov(wordChain, inputText);
    vector<string> inputWords = tokenise(inputText, ' ');
    string lastWord = inputWords.back();
    string output;

    for (int i = 0; i < 5; i++) {

        string nexts = wordChain[lastWord];

        if (nexts.size() > 0) {

            vector<string> nextWords = tokenise(nexts, ' ');
            string nextWord = nextWords[ofRandom(nextWords.size())];
            output += nextWord + " ";
            lastWord = nextWord;

        }
        else {

            vector<string> words = getMapKeys(wordChain);
            lastWord = words[ofRandom(words.size())];
            output += lastWord + " ";

        }

    }
    //add your input to the messageBuffer
    messageBuffer.push_front("markovBot>> " + output);

}

void ofApp::onTextChange(string& text){
    if(text != ""){
        cout << text << endl;
        messageBuffer.push_front("user>> " + text);
        
        //get a response from your bot
        parrotBot(text);
        phraseBot(text);
        mangleBot(text);
        markovBot(text);

        //clear the text input field so the UX feels nicer
        textParameter.set("");
    }
}


// tokenizer - splits the sent string on the sent seperator and sends it back as a vector
// of strings. e.g 'hello how are you' -> {"hello", "how", "are", "you"}
vector<string> ofApp::tokenise(string input, char sep){
    vector<string> vec;
    int end;
    int start = input.find_first_not_of(sep, 0);
    string token;

    //  std::cout << "processing '"<< input << "'" << input.length() << std::endl;
    // find index of sep
    do{
        end = input.find_first_of(sep, start);
        //std::cout << start << " - " << end << std::endl;
        if (start == input.length() || start == end){// whitespace at the end
            break;
        }
        if (end >= 0){// we found it - use end for substr
            token = input.substr(start, end - start);
        }
        else { // we did not find it, use the remaining length of the string
            token = input.substr(start, input.length() - start);
        }
        //std::cout << "got token " << token << std::endl;
        vec.push_back(token);
        // did we find it?
        start = end + 1;
    } while (end > 0);  // yes? continue
  
    return vec;
}

// updates the sent map by adding the sent vector of words to it
// with first order analyis. e.g.:
// input: hello how are you ->
// action: add the following entries to the map:
// hello -> how
// how -> are
// are -> you
// returns the updated map
map <string, string> ofApp::addWordsToMarkov(map <string,string> markov, string words){
  string now, prev, nexts;
  vector <string> tempStrings = tokenise(words, ' ');
  // iterate the word sequence
  
  for (int i=1; i<tempStrings.size();i++){
    //    std::cout << " adding " << tempStrings[i] << " to the chain ";
    // for each word, look up the previous word
    now = tempStrings[i];
    prev = tempStrings[i-1];
    // use the previous word as a key in the map
    nexts = markov[prev];
    // add the new 'observation' for a word following prev to the string
    nexts += now + " ";
    // put it back onto the map
    markov[prev] = nexts;
    //    std::cout << "obs following " << prev << " updated to '" << nexts << "'" << std::endl;
  }
  
  return markov;
}

// returns a vector of strings representing the string keys of the sent map
vector<string> ofApp::getMapKeys(map<string,string> theMap){
  vector<string> vec;
   // show content:
  // from the example code here:  http://www.cplusplus.com/reference/map/map/begin/
  for (map<string,string>::iterator it=theMap.begin(); it!=theMap.end(); ++it){
    //std::cout << it->first << " => " << it->second << '\n';
    vec.push_back(it->first);
  }
  return vec;
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
