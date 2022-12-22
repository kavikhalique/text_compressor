#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
#include<string.h>
#include<math.h>
using namespace std;

class node{
    public:
    char chr;
    int sum;
    node* left;
    node* right;
    node(){
        chr='\0';
        sum=0;
        left=NULL;
        right=NULL;
    }
};

void printCode(unordered_map<char,string>& code_map){
        if(code_map.size()==0){
            cout<<"No Sequence is given(input sequence from option 1 first)";
            return;
        }
        cout<<"\n Enter definite character\n";
        char chr;
        cin>>chr;
        if(code_map[chr].size()==0){
            cout<<"Character is invalid for given string";
            return;
        }
        cout<<code_map[chr]<<endl;
        return;
}

void mapper(node* head,string& binary,unordered_map<char,string> &map){
    if(head==NULL){
        return;
    }
    if(head->chr!='\0'){
        map[head->chr]=binary;
        return;
    }
    binary.push_back('0');
    mapper(head->left,binary,map);
    binary.pop_back();
    binary.push_back('1');
    mapper(head->right,binary,map);
    binary.pop_back();
    return;
}

void printMap(unordered_map<char,string>& code_map){
    if(code_map.size()==0){
            cout<<"No Sequence is given(input sequence from option 1 first)";
            return;
        }
    for(auto i=code_map.begin();i!=code_map.end();i++){
        cout<<i->first<<" "<<i->second<<endl;
    }
}

unordered_map<char,string> encoding(unordered_map<char,int> &freq){
        unordered_map<int,queue<char>> rev_freq;
        unordered_map<int,queue<node*>> pointer;
        priority_queue<int,vector<int>,greater<int>> min_freq;
        for(auto i=freq.begin();i!=freq.end();i++){
            min_freq.push(i->second);
            rev_freq[i->second].push(i->first);
        }
        node* head=NULL;
        while(min_freq.size()>1){
            node *mainNode=new node;
            int first=min_freq.top();
            min_freq.pop();
            if(pointer[first].size()!=0){
                mainNode->left=pointer[first].front();
                pointer[first].pop();
                mainNode->sum+=first;
            }
            else{
                node* left=new node;
                left->chr=rev_freq[first].front();
                rev_freq[first].pop();
                left->sum=first;
                mainNode->sum+=first;
                mainNode->left=left;
            }
            int second=min_freq.top();
            min_freq.pop();
            if(pointer[second].size()!=0){
                mainNode->right=pointer[second].front();
                pointer[second].pop();
                mainNode->sum+=second;
            }
            else{
                node *right=new node;
                right->chr=rev_freq[second].front();
                rev_freq[second].pop();
                right->sum=second;
                mainNode->sum+=second;
                mainNode->right=right;
            }
            min_freq.push(mainNode->sum);
            pointer[mainNode->sum].push(mainNode);
            head=mainNode;
            }
            string code;
            unordered_map<char,string> code_table;
            mapper(head,code,code_table);
            return code_table;
}

unordered_map<char,string> Encoding(string &input){
            unordered_map<char,int> freq;
        for(int i=0;i<input.length();i++){
            freq[input[i]]++;
        }
        return encoding(freq);
}

void decoder(unordered_map<string,char> codeToStr,string str){
        for(int i=0;i<str.length();i++){
            string temp;
            for(;i<str.length();i++){
                temp+=str[i];
                if(codeToStr.count(temp)!=0){
                    cout<<codeToStr[temp];
                    break;
                }
            }
        }
        return;
}

unordered_map<string,char> mapReverser(unordered_map<char,string> map){
        unordered_map<string,char> resultant;
        for(auto i=map.begin();i!=map.end();i++){
            resultant[i->second]=i->first;
        }
        return resultant;
}

void Decoder(string input){
    cout<<" Do you want to use previous Encoded sequence to decode?\n 1.yes\n 2.no\n>>";
    int choice;
    cin>>choice;
    unordered_map<string,char> reversed_map;
    if(choice==1){
        cout<<input<<endl;
    }
    else{
        cout<<"Enter number of different characters"<<endl;
        int n;
        cin>>n;
        cout<<"Enter the character and after space enter its corresponding Encoded Binary Sequence\n\n";
        for(int i=0;i<n;i++){
            char chr;
            string str;
            cin>>chr>>str;
            reversed_map[str]=chr;
        }
        cout<<"Enter the Binary Code which you want to decode using above table"<<endl;
        string input;
        cin>>input;
        decoder(reversed_map,input);
    }
    return;
}

void DecodeWithFreq(){
    cout<<"Enter the total number of characters"<<endl;
    int n;
    cin>>n;
    cout<<"Enter the character and frequency of it in your decoded sequence\n>>";
    unordered_map<char,int> freq;
    for(int i=0;i<n;i++){
        char chr;
        int num;
        cin>>chr>>num;
        freq[chr]=num;
    }
    cout<<endl;
    cout<<"Please Enter the Binary Encoded sequence which you want to Decode\n>>";
    string input;
    cin>>input;
    unordered_map<char,string> code_map= encoding(freq);
    unordered_map<string,char>reversed_map= mapReverser(code_map);
    decoder(reversed_map,input);
    return;
}

void calculateAndPrint(string binary,string text){
    int text_length=text.length();
    int code_length=binary.length();
    int gap=(8*text_length)-code_length;
    cout<<endl;
    cout<<gap<<" bits saved"<<endl;
    cout<<gap/8<<" bytes saved"<<endl;
    float pct= (gap/(float)(8*text_length))*100;
    cout<<pct<<"%"<<" space saved"<<endl;
}

void calculator(string input,unordered_map<char,string> code_map){
    string binary;
    if(input.length()==0){
                        cout<<"First input any string to calculate Efficiency"<<endl;
                        return; 
                    }
    else{
        for(int i=0;i<input.length();i++){
                binary+=code_map[input[i]];
        }
        calculateAndPrint(binary,input);
    }
    return;
}

int main(){
        unordered_map<char,string> code_map;
        string input;
        while(1){
            cout<<"\n Choose any number to perform operation\n 1.Encode any sequence\n 2.Print Encoded Binary Code\n 3.Print corresponding Encoded Value of Each character\n 4.Print Encoded binary value of a single character\n 5.Decode any Precoded sequence(Using Corresponding Encoded binary of each involved character)\n";
            cout<<" 6.Decode any Precoded sequence(Using corresponding frequency of each involved character)\n 7.Calculate how many space saved by compression\n 8.Exit";
         cout<<endl<<">>";
         int choice;
         cin>>choice;
         switch(choice){
            case 1: {cout<<"Please Enter the String which you want to compress\n";
                    cin>>input;
                    code_map= Encoding(input);
                    break;}
            
            case 2: {
                    if(code_map.size()==0){
                        cout<<"No Sequence is given(input sequence from option 1 first)";
                    } 
                    for(int i=0;i<input.length();i++){
                            cout<<code_map[input[i]];
                        }
                    break;}
            
            case 3: printMap(code_map); 
                    break;
            
            case 4: printCode(code_map);
                    break;
            
            case 5: Decoder(input);
                    break;
           
            case 6: DecodeWithFreq();
                    break;

            case 7: calculator(input,code_map);
                    break;

            case 8: exit(0);
            
            default: cout<<"wrong number selected";
         }
        }

        string binary;
        cout<<endl;
        
        //for binary digit to unsigned integer number conversion

            // for(int i=binary.length()-1;i>=0;i--){
            //     unsigned int temp=0;
            //     for(int k=0;i>=0&&k<32;i--,k++){
            //         temp+=(binary[i]-'0')*pow(2,k);
            //     }
            //     cout<<temp;
            //     if(i>=0){
            //         cout<<",";
            //     }
            // }
}
