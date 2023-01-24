// Hadi Hamid 
// reinamez
// 036 
// 11-15-2022

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// c269759b-5ea7-4702-bff4-ebc05443d45d
//------------------------------------------------------



// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>
#include <fstream> //necessary for files
#include <algorithm> //necessary for "max" and "min" helper functions

// This #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"



using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


//declaring necessary vectors to determine sum of each category
vector<int> reviewNumbers;
vector<string> allTruthful;
vector<string> allDeceptive;
vector<string> allUncategorized;


int main(){

    // TODO: implement the main program
  
   //reading in keywordWeights.txt
    ifstream keywordFile("keywordWeights.txt");
  
   //declaring vectors used in functions
    vector<string> keywords;
    vector<double> weights;
    vector<string> reviewWords; 
    
    //socre used for truthfullness
    double score = 0;
    string reviewCategory;
    
    //highest vs. lowest score
    double maxScore = 0;
    double minScore = 0;
    int maxScoreReview = 0;
    int minScoreReview = 0;

    //declaring the counter as an integer
    int reviewNumbers = 0;
  
    // displaying an error if the file cannot be opened
    if(!keywordFile.is_open() ){
        cout << "Error: keywordWeights.txt could not be opened." << endl;
        return 1;
    }
    
    
    if(keywordFile.is_open() ){
       
        readKeywordWeights(keywordFile, keywords, weights); // reading keywords and weights and storing them into parallel vectors
        ofstream fout("report.txt");
        fout << "review" << " " << "score" << " " << "category"<< endl;
       
        // for loop of the reviewFiles folder from 0 to 19
        for(int i= 0; i < 101; ++i){
           
           string fileName = makeReviewFilename(i); // using the makeReviewFilename function to take "00" and "01" into account
           ifstream reviewFile(fileName); 
           
           if(!reviewFile.is_open()){
            break;
           }
            ++reviewNumbers; //add counter if opened succesfully to continue loop
            
            readReview(reviewFile , reviewWords); // using the readReview function to the words of each file to a vector of strings
            
            score = reviewScore(reviewWords, keywords, weights);
            cout << score << endl;

            //determining truthful/deceptive/uncategorized
            if(score > SCORE_LIMIT_TRUTHFUL) { // if the score is greater than 3.0, declare it as truthful
                reviewCategory = "truthful";
            } 
            else if(score < SCORE_LIMIT_DECEPTIVE){ // if the score is less than -3.0, declare it as deceptive
                reviewCategory = "deceptive";
            } 
            else { // if the score is uncategorized, declare it as otherwise
                reviewCategory = "uncategorized";
            }
            
            //putting truthful/deceptive/uncategorized into vectors
            if(reviewCategory == "truthful"){
                allTruthful.push_back(reviewCategory);
            } 
            else if(reviewCategory == "deceptive"){
                allDeceptive.push_back(reviewCategory);
            }
            else if(reviewCategory == "uncategorized"){
                allUncategorized.push_back(reviewCategory);
            }
            
            
            reviewWords.clear(); //clear vector after every loop

            if(score > maxScore){ // finding the index of the max score
                maxScoreReview = i;
            }
            if(score < minScore){ // finding the index of the min score
                minScoreReview = i;
            }
            maxScore = max(maxScore, score); // finding the number of the max score
            minScore = min(minScore, score); // finding the number of the min score

            fout << i << " " << score << " " << reviewCategory << endl; // printing out index, scores, and categories
        } 

        //printing all necessary information to report.txt
        fout << " " << endl;
        fout << "Number of reviews: " << reviewNumbers << endl;
        fout << "Number of truthful reviews: " << allTruthful.size() << endl;
        fout << "Number of deceptive reviews: " << allDeceptive.size() << endl;
        fout << "Number of uncategorized reviews: " << allUncategorized.size() << endl;

        fout << " " << endl;
        fout << "Review with highest score: " << maxScoreReview << endl;
        fout << "Review with lowest score: " << minScoreReview << endl;
        fout.close();
    }

}



