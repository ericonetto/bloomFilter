#include <Arduino.h>
#include "BloomFilter.h"


bool isInSringArray(String word,String *targetArray){
  for (int i=0;i<=sizeof(targetArray);i++){
    if (word.equals(targetArray[i])){
      return true;
    }
  }
  return false;
}


void setup() {
  Serial.begin(115200);
  Serial.println("Setup started");
  //Serial.println("sizeof(bite):"+(String)sizeof(bite));

  Serial.println("Setup finished");
  Serial.printf("       Free heap size: %u\n", ESP.getFreeHeap());
  Serial.println("");
}

void runBloomFilter() {
  Serial.println("");
  Serial.println("Building a filter from scratch");

  int n = 20 ;//no of items to add
  float p = 0.05; //false positive probability
  BloomFilter bfFilter= BloomFilter(n,p);

  Serial.println("Filter size: "+(String)bfFilter.getFilterSize());
  Serial.println("False positive Probability: "+(String)bfFilter.getFalseProb());
  Serial.println("Number of hash functions: "+(String)bfFilter.getHashCount());




  // words to be added
  String word_present[] = {"abound","abounds","abundance","abundant","accessable",
  "bloom","blossom","bolster","bonny","bonus","bonuses",
  "coherent","cohesive","colorful","comely","comfort",
  "gems","generosity","generous","generously","genial"};

  // word not added
  String word_absent[] = {"bluff","cheater","hate","war","humanity",
  "racism","hurt","nuke","gloomy","facebook",
  "geeksforgeeks","twitter"};


  String test_words[] = {"abound","abounds","abundance","abundant","accessable",
  "bloom","blossom","bolster","bonny"," bluff","cheater","hate","war","humanity",
  "racism","hurt","nuke","gloomy","facebook","geeksforgeeks","twitter"};


  Serial.printf("       Free heap size: %u\n", ESP.getFreeHeap());
  Serial.println("");
  delay(100);
  Serial.println("Adding items");
  int numElements=sizeof(word_present)/sizeof(word_present[0]);

  for (int i=0;i<numElements;i++){
    Serial.println("Adding item : " + word_present[i]);
    bfFilter.addItem((char*)word_present[i].c_str());

  }

  std::vector<bool> myFilter=bfFilter.getFilter();
  Serial.println();
  Serial.print("myFilter= {");
  for(int i=0;i<=myFilter.size()-1;i++){
    Serial.print((String)myFilter[i]);
    if(i<myFilter.size()-1){
      Serial.print(", ");
    }
  }
  Serial.println("}");

  delay(3000);

  Serial.println("");
  Serial.println("Testing a already built filter");
  bool myTestFilter[]= {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0,
    1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
    0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0,
    1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0,
    1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 1, 1, 1, 0, 0, 1, 1, 1};

  int myFilterSize=sizeof(myTestFilter)/sizeof(bool);


  BloomFilter bfFilterTest= BloomFilter(n,myTestFilter,myFilterSize);

  Serial.println("Filter size: "+(String)bfFilterTest.getFilterSize());
  Serial.println("False positive Probability: "+(String)bfFilterTest.getFalseProb());
  Serial.println("Number of hash functions: "+(String)bfFilterTest.getHashCount());



  Serial.printf("       Free heap size: %u\n", ESP.getFreeHeap());
  Serial.println("");
  Serial.println("Testing items...");
  for (int i=0;i<numElements;i++){
    char *word=(char*)test_words[i].c_str();
    if (bfFilterTest.checkItem(word)){
      if (isInSringArray(test_words[i],word_absent)){
        Serial.println(test_words[i] + " is a false positive!!!!!");
      }else{
        Serial.println(test_words[i] + " prob. present");
      }
    }else{
      Serial.println(test_words[i] + " not present!");

    }

  }

  Serial.printf("       Free heap size: %u\n", ESP.getFreeHeap());
  delay(6000);

}



void loop() {
  runBloomFilter();
}
