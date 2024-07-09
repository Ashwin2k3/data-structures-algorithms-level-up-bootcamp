
## ./01 Arrays & Vectors
### 01 vector.cpp

```cpp
#include<iostream>
#include<vector>
using namespace std;

int main(){
	//Demo Vector
	//vector<int> arr =  //{1,2,10,12,15};

	//Fill Constructor
	vector<int> arr(10,7);

	//Fill Constructor
	vector<int> visited(100,0);

	//Pop_back
	arr.pop_back();
	// Push_Back O(1)
	arr.push_back(16);

	//Print all the elements
	for(int x : arr){
		cout << x <<",";
	}

	/*for(int i=0;i< arr.size(); i++){
		cout << arr[i] <<endl;
	}*/

	return 0;
}
```

### 02 2dvector.cpp

```cpp
#include<iostream>
#include<vector>
using namespace std;


int main(){
	//2D Vector 
	vector< vector<int> > arr =  {
		{1,2,3},
		{4,5,6},
		{7,8,9,10},
		{11,12}};


	arr[0][0] += 10; //update

	for(int i=0;i< arr.size(); i++){

		for(int number : arr[i]){
			cout << number <<",";
		}
		cout <<endl;
	}
	

	return 0;
}
```

### 04 triplets.cpp

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int> > triplets(vector<int> arr,int targetSum){
	//Logic 
	int n = arr.size();
	sort(arr.begin(),arr.end());
	vector<vector<int> > result;

	// Pick every a[i], pair sum for remaining part
	for(int i=0; i<=n-3;i++){

		int j = i + 1;
		int k = n - 1;

		//two pointer approach
		while(j < k){
			int current_sum = arr[i];
			current_sum += arr[j];
			current_sum += arr[k];

			if(current_sum==targetSum){
				result.push_back({arr[i],arr[j],arr[k]});
				j++;
				k--;
			}
			else if(current_sum > targetSum){
				k--;
			}
			else{
				j++;
			}
		}

	}
	return result;

}

int main(){

	vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 15};
	int S = 18;

	auto result = triplets(arr,S);

	for(auto v : result){
		for(auto no : v){
			cout<<no<<",";
		}
		cout<<endl;
	}


	return 0;
}
```

### 05 mountain.cpp

```cpp
#include<iostream>
#include<vector>
using namespace std;


int highest_mountain(vector<int> a){
	int n = a.size();

	int largest = 0;

	for(int i=1;i<=n-2;){

		//check a[i] is peak or not
		if(a[i]>a[i-1] and a[i]>a[i+1]){
			//do some work
			int cnt = 1;
			int j = i;
			//cnt backwards (left)
			while(j>=1 and a[j]>a[j-1]){
				j--;
				cnt++;
			}
			//cnt forwards (right)
			while(i<=n-2 and a[i]>a[i+1]){
				i++;
				cnt++;
			}
			largest = max(largest,cnt);

		}
		else{
			i++;
		}
	}
	return largest;

}

int main(){

	vector<int> arr{5,6,1,2,3,4,5,4,3,2,0,1,2,3,-2,4};

	cout<< highest_mountain(arr)<<endl;



	return 0;
}
```

### 06 longest_band.cpp

```cpp
#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

int largestBand(vector<int> arr){
	int n = arr.size();
	unordered_set<int> s;
	
	//Data inside a set
	for(int x : arr){
		s.insert(x);
	}

	//Iterate over the arr
	int largestLen = 1;

	for(auto element : s){
		int parent = element - 1;

		if(s.find(parent)==s.end()){
			//find entire band / chain starting from element
			int next_no = element + 1;
			int cnt = 1;

			while(s.find(next_no)!=s.end()){
				next_no++;
				cnt++;
			}

			if(cnt>largestLen){
				largestLen = cnt;
			}
		}
	}


	return largestLen;
}



int main(){

	vector<int> arr{1, 9, 3, 0, 18, 5, 2, 10, 7, 12, 6};
	cout << largestBand(arr)<<endl;

	return 0;
}
```

### 07 rainwater-trap.cpp

```cpp
#include <iostream>
#include <vector>
using namespace std;


int trappedWater(vector<int> heights) {

 	//Complete
 	int n = heights.size();
 	if(n<=2){
 		return 0;
 	}

 	//Left Max, Right Max
 	vector<int> left(n,0), right(n,0);
 	left[0] = heights[0];
 	right[n-1] = heights[n-1];

 	for(int i=1;i<n;i++){
 		left[i] = max(left[i-1],heights[i]);
 		right[n-i-1] = max(right[n-i],heights[n-i-1]);
 	}

 	//water 
 	int water = 0;
 	for(int i=0;i<n;i++){
 		water += min(left[i],right[i]) - heights[i];
 	}
	
  return water;
}

int main() {
    vector<int> water = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout<<trappedWater(water)<<endl;
    return 0;
}

```

### 08 subarray_sort.cpp

```cpp
#include <iostream>
#include<algorithm>
#include <vector>
using namespace std;

bool outOfOrder(vector<int> arr,int i){
	int x = arr[i];
	if(i==0){
		return x > arr[1];
	}
	if(i==arr.size()-1){
		return x < arr[i-1];
	}
	return x > arr[i+1] or x < arr[i-1];

}

pair<int,int> subarraySort(vector<int> arr) {

	int smallest = INT_MAX;
	int largest = INT_MIN;

	for(int i=0;i<arr.size();i++){
		int x = arr[i];
		
		if(outOfOrder(arr,i)){
			smallest = min(smallest,x);
			largest = max(largest,x);
		}
	}

	//next step find the right index where smallest and largest lie (subarray) for out solution
	if(smallest==INT_MAX){
		return {-1,-1};
	}

	int left = 0;
	while(smallest >= arr[left]){
		left++;
	}
	int right = arr.size() - 1;
	while(largest <= arr[right]){
		right--;
	}

	return {left,right};

}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 8, 6, 7, 9, 10, 11};
    auto p = subarraySort(arr);
    cout<< p.first <<" and "<<p.second <<endl;

    return 0;
}

```

### 09 min_swaps.cpp

```cpp
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

int countMinSwaps(vector<int> arr){

    // Know the actual positions of elements (sorting)
    //store the current indices
    int n = arr.size();
    pair<int,int> ap[n];
    for(int i=0;i<n;i++){
        ap[i].first = arr[i];
        ap[i].second = i;
    }

    //sorting
    sort(ap,ap+n);

    //build the main logic
    vector<bool> visited(n,false);

    int ans = 0;
    for(int i=0;i<n;i++){

        // if element is visited or element is in right postion 
        int old_position = ap[i].second;
        if(visited[i]==true or old_position==i){
            continue;
        }

        // visiting the element (index) for first time 
        int node = i;
        int cycle = 0;

        while(!visited[node]){
            visited[node] = true;
            int next_node = ap[node].second;
            node = next_node;
            cycle += 1;
        }
        ans += (cycle-1);

    }
   
    return ans;

}


int main() {
    vector<int> arr{5,4,3,2,1};
    cout<<countMinSwaps(arr)<<endl;
    return 0;
}

```

### fizzbuzz.cpp

```cpp
#include<iostream>
#include<vector>
#include<string>
using namespace std;

//Complete this method, don't write main
vector<string> fizzbuzz(int n){
    
    vector<string> result;
    for(int i=1;i<=n;i++){
        if((i%15)==0){
            result.push_back("FizzBuzz");
        }
        else if(i%5 == 0){
            result.push_back("Buzz");
        }
        else if(i%3 == 0){
            result.push_back("Fizz");
        }
        else{
            result.push_back(to_string(i));
        }
        
    }
    
    return result; 
    
}


int main(){

	vector<string> output = fizzbuzz(10);
	for(string x : output){
		cout << x <<",";
	}


	return 0;
}
```

### pairs 03.cpp

```cpp
#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

vector<int> pairSum(vector<int> arr,int Sum){
	//Logic 
	unordered_set<int> s;
	vector<int> result;

	for(int i=0;i<arr.size();i++){

		int x = Sum - arr[i];
		if(s.find(x)!=s.end()){
			result.push_back(x);
			result.push_back(arr[i]);
			return result;
		}
		//insert the current no inside set
		s.insert(arr[i]);
	}
	return {};
}

int main(){

	vector<int> arr{10, 5, 2 , 3, -6, 9 , 11};
	int S = 4;

	auto p = pairSum(arr,S);
	if(p.size()==0){
		cout<<"No such pair";
	}
	else{
		cout<<p[0]<<","<<p[1]<<endl;
	}

	return 0;
}
```

## ./02 Strings
### 00 stringfind.cpp

```cpp
#include<iostream>
#include<string>
using namespace std;


int main(){

	string paragraph = "We are learning about STL strings. STL string class is quite powerful";

	string word;
	getline(cin,word);

	//find function
	int index =  paragraph.find(word);

	if(index!=-1){
		cout <<"first occ" <<index;
	}

	index = paragraph.find(word,index+1);

	if(index!=-1){
		cout<<"second occ "<<index <<endl;
	}



	return 0;
}
```

### 01 string_find_all.cpp

```cpp
#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<int> stringSearch(string big,string small){
    
    vector<int> result;
    int index = big.find(small);
    while(index!=-1){
    	result.push_back(index);
    	index = big.find(small,index+1);
    }
    
    return result;
}

int main(){

	string paragraph = "We are learning about STL strings. STL string class is quite powerful";

	string word = "STL";

	vector<int> result = stringSearch(paragraph,word);
	for(int x:result){
		cout <<x<<",";
	}

	return 0;
}
```

### 02 space20.cpp

```cpp
#include <iostream>
#include<cstring>
using namespace std;

void replace_space(char *str){

    //1. calc spaces 
    int spaces = 0;
    for(int i=0;str[i]!='\0';i++){
        if(str[i]==' '){
            spaces += 1;
        }
    }

    int idx = strlen(str) + 2*spaces;
    str[idx] = '\0';

    for(int i= strlen(str)-1;i>=0;i--){
        if(str[i]==' '){
            str[idx-1] = '0';
            str[idx-2] = '2';
            str[idx-3] = '%';
            idx = idx - 3;
        }
        else{
            str[idx-1] = str[i];
            idx--;
        }
    }

}


int main() {
    char input[10000];
    cin.getline(input,1000);
    replace_space(input);
    cout<<input <<endl;

    return 0;
}

```

### 03 tokenisation_sstream.cpp

```cpp
#include<iostream>
#include<sstream>
#include<vector>
#include<cstring>
using namespace std;


int main(){

	string input;
	getline(cin,input);
	//"this is a sunny day"

	//create a string stream object
	stringstream ss(input);

	// >> and << operators 
	string token;
	vector<string> tokens;
	while(getline(ss,token,' ')){
		tokens.push_back(token);
	}

	//print all all tokens
	for(auto token:tokens){
		cout<<token<<",";
	}





	return 0;
}
```

### 04 mystrtok.cpp

```cpp
#include <iostream>
using namespace std;

char *mystrtok(char *str,char delim){

    static char *input = NULL;
    
    if(str!=NULL){
        input = str;
    }
    if(input==NULL){
        return NULL;
    }
    //static
    char *token = new char[strlen(input)+1];
    int i=0;

    for( ; input[i]!='\0';i++){
        if(input[i]!=delim){
            token[i] = input[i];
        }
        else
        {
            token[i] = '\0';
            input = input + i + 1;
            return token;
        }
    }

    //out of the loop
    token[i] = '\0';
    //reset the input as nULL
    input = NULL;
    return token;
}


int main(){

    char s[1000];
    cin.getline(s,1000);

   //strtok()
     char *token =  mystrtok(s,' ');
     

     while(token!=NULL){
        cout<<token <<endl;
        token = mystrtok(NULL,' ');
     }

    return 0;
}
```

### 05 strtok_use.cpp

```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;


int main(){

    char input[1000];
    cin.getline(input,1000);

   //strtok()
     char *token =  strtok(input," ");
     

     while(token!=NULL){
        cout<<token <<endl;
        token = strtok(NULL," ");
     }

    return 0;
}
```

### 06 sort_strings.cpp

```cpp
/*
Sample Input
------------
3
92 022
82 12
77 13
2 false numeric

Sample Output
-------------
82 12
77 13
92 022

*/
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

string extractStringAtKey(string str,int key){

	//string tokeniser 
	// hello how are you

	char *s = strtok( (char *)str.c_str(), " ");
	while(key>1){
		s = strtok(NULL," ");
		key--;
	}
	return (string)s;
}

int convertToInt(string s){

	int ans = 0;
	int p = 1;

	for(int i=s.length()-1; i>=0;i--){
		ans += ((s[i]-'0')*p);
		p = p*10;
	}
	return ans;
}

bool lexicoCompare(pair<string,string> s1, pair<string,string> s2){
	string key1, key2;
	key1 = s1.second;
	key2 = s2.second;
	return key1 < key2;
}

bool numericCompare(pair<string,string> s1, pair<string,string> s2){
	string key1, key2;
	key1 = s1.second;
	key2 = s2.second;

	return convertToInt(key1) < convertToInt(key2);
}



int main(){
	string s ="20 30 40 50";
	
	
	int n;
	cin>>n;

	cin.get(); //consume the extra \n

	string temp;
	vector<string> v;
	for(int i=0;i<n;i++){
		getline(cin,temp); //includes white spaces 
		v.push_back(temp);
	}

	int key;
	string reversal,ordering;
	cin >>key >> reversal >> ordering; 


	//1. To extract keys for comparison & store them
	vector<pair<string,string> > vp;  

	for(int i=0;i<n;i++){
		vp.push_back({v[i], extractStringAtKey(v[i],key)});
	}

	//2. Sorting 
	if(ordering=="numeric"){
		sort(vp.begin(),vp.end(),numericCompare);
	}
	else{
		sort(vp.begin(),vp.end(),lexicoCompare);
	}


	//3. reversal
	if(reversal=="true"){
		reverse(vp.begin(),vp.end());
	}

	//4. output
	for(int i=0;i<n;i++){
		cout<< vp[i].first << endl;
	}



	return 0;
}








```

### 07 check_subset.cpp

```cpp
#include<iostream>
#include<cstring>
using namespace std;

bool isSubset(string s1,string s2){

	int i = s1.length() - 1;
	int j = s2.length()-1;

	while(i>=0 and j>=0){
		if(s2[j]==s1[i]){
			i--;
			j--;
		}
		else{
			i--;
		}
	}
	if(j==-1){
		return true;
	}
	return false;

}


int main() {
    string s1,s2;
    cin>>s1>>s2;
    cout<<isSubset(s1,s2) <<endl;
    
}

```

### 08 sort subsequence.cpp

```cpp
#include <iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
//sorted subsequences
void subsequence(string s,string o, vector<string> &v){
	//base case
	if(s.size()==0){
		v.push_back(o);
		return;
	}

	//rec case
	char ch = s[0];
	string reduced_input = s.substr(1);

	//includes
	subsequence(reduced_input, o + ch, v);

	//excludes
	subsequence(reduced_input, o , v);
}
bool compare(string s1,string s2){
	if(s1.length()==s2.length()){
		return s1 < s2;
	}
	return s1.length() < s2.length();

}

int main(){

	string s;
	cin>>s;
	vector<string> v;
	string output = "";
	subsequence(s,output,v);

	sort(v.begin(),v.end(),compare);

	for(auto s : v){
		cout<< s << ",";
	}


	return 0;

}
```

### strings.cpp

```cpp
#include<iostream>
#include<string>
#include<vector>
using namespace std;


int main(){

	//char s[1000] = {'1','a','b','c','\0'};

	string s; //"hello world"; //Dynamic Array

	int n=5;
	vector<string> sarr;
	string temp;

	while(n--){
		getline(cin,temp);
		sarr.push_back(temp);
	}

	for(string x: sarr){
		cout<<x<<","<<endl;
	}

}
```

## ./03 Sliding Window
### 01 housing.cpp

```cpp
#include <iostream>
using namespace std;


void housing(int *arr,int n,int k){

    int i=0;
    int j= 0;
    int cs = 0;

    while(j<n){

        //expand to right
        cs += arr[j];
        j++;

        //remove elements from the left till cs > sum and i<j
        while(cs > k and i<j){
            cs = cs - arr[i];
            i++;
        }

        //check if any given point 
        if(cs==k){
            //print that window
            cout<< i <<" - "<<j-1 <<endl;
        }

    }
    return;
}

int main() {

    //smallest window that contains the reqd sum
    // handle if you have negative integers in the arrays 

    int plots[] = { 1 ,3 ,2 ,1 ,4 ,1 ,3 ,2 ,1 ,1};
    int  n = sizeof(plots)/sizeof(int);
    int k = 8;

    housing(plots,n,k);


    return 0;
}

```

### 02 unique_substring.cpp

```cpp
#include<iostream>
#include<unordered_map>
#include<cstring>
using namespace std;

string unique_substring(string str){

	int i = 0;
	int j = 0;

	int window_len = 0;
	int max_window_len = 0;
	int start_window = -1;


	unordered_map<char,int> m;


	while(j < str.length()){

		char ch = str[j];

		//if it is inside hashmap & its idx >= start of the current window
		if(m.count(ch) and m[ch]>=i){
			//later on..
			i = m[ch] + 1;
			window_len = j - i; //updated remaining window len excluding current char
		}

		//update the last occ 
		m[ch] = j;
		window_len++;
		j++;

		//update max_window_len at every step
		if(window_len > max_window_len){
			max_window_len = window_len;
			start_window = i;
		}
	}
	return str.substr(start_window,max_window_len);
}


int main(){

	string input;
	cin>>input;

	cout << unique_substring(input);


	return 0;
}
```

### 03 string_window.cpp

```cpp
#include<iostream>
#include<climits>
#include<string>
using namespace std;

string find_window(string s,string p){


	//Array as a Freq Map or you can hashmap
	int FP[256] = {0};
	int FS[256] = {0};

	for(int i=0;i<p.length();i++){
		FP[ps[i]]++;
	}

	//Sliding Window Algorithm
	int cnt = 0;
	int start = 0; // left contraction
	int start_idx = -1; //start_idx for best window
	int min_so_far = INT_MAX; //large number
	int window_size ;


	for(int i=0 ; i < s.length(); i++){
		//expand the window by including current character
		char ch = s[i];
		FS[ch]++;

		//Count how many characters have been matched till now (string and pattern)
		if(FP[ch]!=0 and FS[ch]<= FP[ch]){
			cnt += 1;
		}

		//another thing 
		//if all characters of the pattern are found in the current window then you can start contracting
		if(cnt==p.length()){

			//start contracting from the left to remove unwanted characters 
			
			while(FP[s[start]]==0 or FS[s[start]] > FP[s[start]]){
				FS[s[start]]--;
				start++;
			}

			//note. the window size
			window_size = i - start + 1;
			if(window_size < min_so_far){
				min_so_far = window_size;
				start_idx = start;
			}

		}

	}
	if(start_idx==-1){
		return "No window found";
	}
	return s.substr(start_idx,min_so_far);
}



int main(){

	string s,p;
	cin>>s>>p;


    cout<<find_window(s,p)<<endl;



	return 0;
}
```

## ./04 Sorting & Searching
### 01 mergesort_vector.cpp

```cpp
#include<iostream>
#include <vector>
using namespace std;

//helper method
void merge(vector<int> &array,int s,int e){
	int i = s;
	int m = (s+e)/2;
	int j = m + 1;

	vector<int> temp;


	while(i<=m and j<=e){
		if(array[i] < array[j]){
			temp.push_back(array[i]);
			i++;
		}
		else{
			temp.push_back(array[j]);
			j++;
		}
	}

	//copy rem elements from first array
	while(i<=m){
		temp.push_back(array[i++]);
	}

	// or copy rem elements from second array
	while(j<=e){
		temp.push_back(array[j++]);
	}

	//copy back the eleemtns from temp to original array
	int k = 0 ;
	for(int idx = s; idx <=e ;idx++){
		array[idx] = temp[k++];
	}
	return;
}

//sorting method
void mergesort(vector<int> &arr,int s,int e){
	//base case
	if(s>=e){
		return;
	}
	//rec case
	int mid = (s+e)/2;
	mergesort(arr,s,mid);
	mergesort(arr,mid+1,e);
	return merge(arr,s,e);
}

int main(){
  	
  	vector<int> arr{10,5,2,0,7,6,4};

	int s = 0;
	int e = arr.size()-1;
  	mergesort(arr,s,e);
	for(int x : arr){
		cout<< x <<",";
	}
	cout<<endl;
	return 0;
}





```

### 02 inversion_count.cpp

```cpp
#include<iostream>
#include <vector>
using namespace std;

//helper method
int merge(vector<int> &array,int s,int e){
	int i = s;
	int m = (s+e)/2;
	int j = m + 1;

	vector<int> temp;

	int cnt = 0;

	while(i<=m and j<=e){
		if(array[i] < array[j]){
			temp.push_back(array[i]);
			i++;
		}
		else{
			cnt += (m - i + 1);
			temp.push_back(array[j]);
			j++;
		}
	}

	//copy rem elements from first array
	while(i<=m){
		temp.push_back(array[i++]);
	}

	// or copy rem elements from second array
	while(j<=e){
		temp.push_back(array[j++]);
	}

	//copy back the eleemtns from temp to original array
	int k = 0 ;
	for(int idx = s; idx <=e ;idx++){
		array[idx] = temp[k++];
	}
	return cnt;
}

//sorting method
int inversion_count(vector<int> &arr,int s,int e){
	//base case
	if(s>=e){
		return 0;
	}
	//rec case
	int mid = (s+e)/2;
	int C1 = inversion_count(arr,s,mid);
	int C2 = inversion_count(arr,mid+1,e);
	int CI =  merge(arr,s,e);
	return C1 + C2 + CI;
}

int main(){
  	
  	vector<int> arr{0,5,2,3,1};

	int s = 0;
	int e = arr.size()-1;
  	cout<< inversion_count(arr,s,e) <<endl;
	
	cout<<endl;
	return 0;
}





```

### 03 quicksort.cpp

```cpp
#include<iostream>
#include <vector>
using namespace std;


int partition(vector<int> &a,int s,int e){

	int pivot = a[e];
	int i = s - 1;

	for(int j=s;j<e;j++){
		if(a[j] < pivot){
			i++;
			swap(a[i],a[j]);
		}
	}
	
	swap(a[i+1],a[e]);
	return i + 1;
	
}

void quicksort(vector<int> &a, int s,int e){
	//Base Case
	if(s>=e){
		return;
	}
	//Rec Case
	int p = partition(a,s,e);
	quicksort(a,s,p-1);
	quicksort(a,p+1,e);
}


int main(){
    vector<int> arr{10,5,2,0,7,6,4};
    cout<< arr.size() <<endl;
    int n = arr.size();

    quicksort(arr,0,n-1);

    for(int x :arr){
    	cout << x << " ";
    }

    return 0;
}

```

### 04 quickselect.cpp

```cpp
#include<iostream>
#include <vector>
using namespace std;


int partition(vector<int> &a,int s,int e){

	int pivot = a[e];
	int i = s - 1;

	for(int j=s;j<e;j++){
		if(a[j] < pivot){
			i++;
			swap(a[i],a[j]);
		}
	}
	
	swap(a[i+1],a[e]);
	return i + 1;
	
}

int quickselect(vector<int> a, int s,int e,int k){

	//assuming that k will be inside the array

	int p = partition(a,s,e);
	if(p==k){
		return a[p];
	}
	else if(k<p){
		return quickselect(a,s,p-1,k);
	}		
	else{
		return quickselect(a,p+1,e,k);
	}
	
}


int main(){
    vector<int> arr{10,5,2,0,7,6,4};
    //cout<< arr.size() <<endl;
    int n = arr.size();
    int k ;
    cin>>k;

    cout <<quickselect(arr,0,n-1,k);

    return 0;
}

```

### 05 smallest_string.cpp

```cpp
#include <iostream>
#include<algorithm>
#include<cstring>
using namespace std;

bool compare(string x,string y){
	return x + y < y + x;
}


int main() {
    string arr[] = {"a","ab","aba"};
    int n = 3;

    sort(arr,arr+n,compare);

    for(auto s : arr){
    	cout <<s;
    }



    return 0;
}

```

### 06 sparse_search.cpp

```cpp
#include <iostream>
#include<cstring>
using namespace std;

int sparse_search(string a[],int n,string key){
    
    // sparse search
    int s=0;
    int e = n-1;
    while(s<=e){
        int mid = (s+e)/2;
        int mid_left = mid - 1;
        int mid_right = mid + 1;
        if(a[mid]==""){
            while(1){
                if(mid_left<s and mid_right>e){
                    return -1;
                }
                else if(mid_right<=e and a[mid_right]!=""){
                    mid = mid_right;
                    break;
                }
                else if(mid_left>=s and a[mid_left]!=""){
                    mid = mid_left;
                    break;
                }
                mid_left--;
                mid_right++;
            }
        }
        if(a[mid]==key){
            return mid;
        }
        else if(a[mid] > key){
            e = mid - 1;
        }
        else{
            s = mid + 1;
        }
    }
    return -1;
}

int main() {
    string arr[] = {"ai", "", "","bat", "","","car","cat","","","dog",""};
    int n = 12;

    string f;
    cin>>f;
    cout<<sparse_search(arr,n,f)<<endl;


    return 0;
}

```

## ./05 Binary Search
### 01 Frequency Count.cpp

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int lower_bound(vector<int> arr,int key){

	int s = 0;
	int e = arr.size() - 1;

	int ans = -1;

	while(s<=e){
		int mid = (s+e)/2;

		if(arr[mid]==key){
			ans = mid;
			e = mid - 1;
		}
		else if(arr[mid] > key){
			e = mid - 1;
		}
		else{
			s = mid + 1;
		}
	}
	return ans;

}
int upper_bound(vector<int> arr,int key){

	int s = 0;
	int e = arr.size() - 1;

	int ans = -1;

	while(s<=e){
		int mid = (s+e)/2;

		if(arr[mid]==key){
			ans = mid;
			s = mid + 1;
		}
		else if(arr[mid] > key){
			e = mid - 1;
		}
		else{
			s = mid + 1;
		}
	}
	return ans;

}


int main(){

	vector<int> arr = {0,1,1,2,3,3,3,3,3,4,5,5,5,10};
	int n = arr.size();

	cout<< upper_bound(arr,3) - lower_bound(arr,3)   + 1 <<endl;

	//STL
	cout << upper_bound(arr.begin(),arr.end(),3) - lower_bound(arr.begin(),arr.end(),3)<<endl;


	return 0;
}
```

### 02 rotated_search.cpp

```cpp
#include<iostream>
#include<vector>
using namespace std;

int rotated_search(vector<int> a,int key) {
	int n = a.size();

	//Logic
	int s = 0;
	int e = n - 1;

	while(s<=e){
		int mid = (s+e)/2;

		if(a[mid]==key){
			return mid;
		}

		//2 cases
		if(a[s]<=a[mid]){
			//left
			if(key>=a[s] and key<=a[mid]){
				e = mid - 1;
			}
			else{
				s = mid + 1;
			}

		}
		else{
			//right

			if(key>=a[mid] and key<=a[e]){
				s = mid + 1;
			}
			else{
				e = mid - 1;
			}

		}

	}
	return -1;

}



int main() {

	
	vector<int> a{4,5,6,7,0,1,2,3};
	int key;
	cin>>key;
	cout<< rotated_search(a,key) <<endl;
	return 0;
}
```

### 03 square_root.cpp

```cpp
#include<iostream>
using namespace std;

float square_root(int N,int P){
    int s = 0;
    int e = N ;
    float ans = 0;

    //Binary Search (Search Space 0....N)
    while(s<=e){
    	int mid = (s+e)/2;
    	if(mid*mid==N){
    		return mid;
    	}
    	else if(mid*mid < N){
    		ans = mid;
    		s = mid + 1;
    	}

    	else{
    		e = mid - 1;
    	}

    }

    //Linear Search for each place (for floating part)
    float inc = 0.1;

    for(int place=1;place<=P;place++){

    	//do linear search
    	while(ans*ans <=N){
    		ans += inc;
    	}

    	//take one step back
    	ans = ans - inc;
    	inc = inc/10.0;
    }

   
    return ans;
}



int main(){

	int n,p;
	cin>>n>>p;

	cout<<square_root(n,p)<<endl;

	return 0;
}
```

### 04 angry_birds.cpp

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


bool canPlaceBirds(int B,int N,vector<int> nests,int sep){

	int birds = 1;
	int location = nests[0];

	for(int i=1; i<=N-1; i++){
		int current_location = nests[i];
		if(current_location - location >= sep){
			birds++;
			location = current_location;

			if(birds==B){
				return true;
			}
		}
	}
	return false;

}


int main(){
	int B = 3;
	vector<int> nests{1,2,4,8,9};
	//sorting
	sort(nests.begin(),nests.end());
	int N = nests.size();

	//Binary Search
	int s = 0;
	int e = nests[N-1] - nests[0];
	int ans = -1;

	while(s<=e){
		int mid = (s+e)/2;

		bool canPlace = canPlaceBirds(B,N,nests,mid);
		if(canPlace){
			ans = mid;
			s = mid + 1;
		}
		else{
			e = mid - 1;
		}
	}

	cout << ans <<endl;

	return 0;
}
```

### 05 min_pairs.cpp

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;

void min_pair(vector<int> a1,vector<int> a2){


	//Sort the array
	sort(a2.begin(),a2.end());

	int p1,p2;
	int diff = INT_MAX;

	//iteratte over 1 array and look for closes elements in the second array
	for(int x : a1){
		auto lb = lower_bound(a2.begin(),a2.end(),x) - a2.begin();

		//left
		if(lb>=1 and x - a2[lb-1] < diff){
			diff = x - a2[lb-1];
			p2 = x;
			p1 = a2[lb-1];
		}
		//greater / right
		if(lb!=a2.size() and a2[lb]-x < diff){
			diff = a2[lb] - x;
			p1 = x;
			p2 = a2[lb];
		}

	}
	cout<<"Min Pair "<<p1<<" and "<<p2 <<endl;
	return;

}


int  main(){

	vector<int> a1 = {-1, 5, 10, 20, 3};
	vector<int> a2 = {26, 134, 135, 15, 17};
	min_pair(a1,a2);


	return 0;
}
```

### kpartition.cpp

```cpp
#include <iostream>
using namespace std;

bool divideAmongK(int arr[],int n,int k,int limit){
    //return true if every partition gets atleast limit no of coins

        int cnt = 0;
        int current_sum = 0;
        
        for(int i=0;i<n;i++){
            if(current_sum + arr[i] >=limit){
                cnt +=1;
                current_sum = 0;
            }
            else{
                current_sum += arr[i];
            }
        } 
       
    return cnt>=k;
}

int k_partition(int arr[],int n,int k){
   
    int e = 0;
    int s = 0;
    for(int i=0;i<n;i++){
        e += arr[i];
    }
    //mid
    int mid;
    int ans;
    //search range (s,e)
    while(s<=e){
         mid = (s+e)/2;
         
        bool isPossible = divideAmongK(arr,n,k,mid);

        if(isPossible){
            s = mid + 1;
            ans = mid;
        }
        else{
            e = mid - 1;
        }
    }
    return ans;

}
int main() {
    int a[] = {1,2,3,4};
    int n  = sizeof(a)/sizeof(int);
    int k = 4;
    cout<< k_partition(a,n,k)<<endl;
    return 0;
}

```

### max_subarray_sliding_window_deque.cpp

```cpp
#include <iostream>
#include<vector>
#include<deque>
using namespace std;

void maxSubArrayK(vector<int> a,int k){

    //Algorithm
    int n = a.size();

    deque<int> Q(k);
    //1. Process only the first K elements
    int i;

    for(i=0;i<k;i++){
        //Logic here ...

        while(!Q.empty() && a[i] > a[Q.back()]){
            Q.pop_back();
        }

        Q.push_back(i);

    }

    //2. Remaining the elements of the array
    for( ;i<n;i++){
        cout << a[Q.front()]<<" ";
        //Remove element from the left (contraction when an index lies outside the current window)
        while(!Q.empty() and Q.front() <=i-k){
            Q.pop_front();
        }
        while(!Q.empty() && a[i] >= a[Q.back()]){
            Q.pop_back();
        }

        //always
        Q.push_back(i);
    }


    cout<< a[Q.front()];

}

int main() {
    
    vector<int> arr{1,2,3,1,4,5,2,3,5};
    int k = 3;

    maxSubArrayK(arr,k);


    
    
    return 0;
}

```

## ./06 Recursion Problems
### Subset Sum to X.cpp

```cpp
#include <iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;


int countSubsets(vector<int> arr,int n,int i,int X){

	//base case
	if(i==n){
		if(X==0){
			return 1;
		}
		return 0;
	}

	//recusive case 
	int inc  = countSubsets(arr,n,i+1,X - arr[i]);
	int exc = countSubsets(arr,n,i+1,X);
	return inc + exc;
}

int main(){
	vector<int> arr{1,2,3,4,5};
	int X = 10;

	cout << countSubsets(arr,arr.size(),0,X)<<endl;

	return 0;

}
```

### Sudoku.cpp

```cpp
#include<iostream>
#include<cmath>
using namespace std;

bool isSafe(int mat[][9],int i,int j,int no){


	//Check for row and col
	for(int k=0;k<9;k++){
		if(mat[k][j]==no||mat[i][k]==no){
			return false;
		}
	}
	//check for subgrid

	int sx = (i/3)*3;
	int sy = (j/3)*3;

	for(int x=sx; x<sx + 3;x++){
		for(int y =sy;y<sy + 3;y++){
			if(mat[x][y]==no){
				return false;
			}
		}
	}
	return true;
}




bool solveSudoku(int mat[][9],int i,int j,int n){
	//base case
	if(i==n){
		//print the solution later
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				cout<<mat[i][j]<<" ";
			}
			cout<<endl;
		}

		return true;
	}

	//rec case
	if(j==n){
		return solveSudoku(mat,i+1,0,n);
	}

	//skip  the prefilled cell
	if(mat[i][j]!=0){
		return solveSudoku(mat,i,j+1,n);
	}

	//cell to be filled
	//try out all possibilites
	for(int no=1;no<=n;no++){
		//whether it is safe to place the number or not
		if(isSafe(mat,i,j,no)){

			mat[i][j] = no;
			bool solveSubproblem = solveSudoku(mat,i,j+1,n);
			if(solveSubproblem==true){
				return true;
			}
		}

	}
	// if no option works, backtracking 
	mat[i][j] = 0;
	return false;
}


int main(){
	int n = 9;
	int mat[9][9] =
        {{5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}};


        if(!solveSudoku(mat,0,0,n)){
        	cout<<"No solution exists!";
        }


}
```

### TODO permutations.cpp

```cpp
#include<iostream>
using namespace std;


void permute(string a,int i){


}


int main(){

	string s;
	cin>>s;
	permute(s);
	return 0;
}
```

### generate_brackets.cpp

```cpp
#include<iostream>
using namespace std;


void generateBrackets(string output,int n,int open,int close,int i){
	//base case
	if(i==2*n){
		cout<<output <<endl;
		return;
	}

	//open 
	if(open<n){
		
		generateBrackets(output + '(',n,open+1,close,i+1);
	}

	//closing 
	if(close<open){
		generateBrackets(output + ')',n,open,close+1,i+1);
	}
}

int main(){

	string output;
	int n ;
	cin>>n;
	generateBrackets(output,n,0,0,0);

	return 0;

}
```

### keypad_input.cpp

```cpp
#include<iostream>
#include<cstring>
using namespace std;

string keypad[] = {"","","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"};


void printKeypadOutput(string input,string output,int i=0){

	if(input[i]=='\0'){
		cout<<output<<endl;
		return;
	}

	//rec case
	int current_digit = input[i] - '0';
	if(current_digit==0 or current_digit==1){
		printKeypadOutput(input,output,i+1);
	}

	//keypad 
	for(int k=0; k<keypad[current_digit].size();k++){
		printKeypadOutput(input,output + keypad[current_digit][k],i+1);
	}
	return;

}




int main(){

	string input;
	cin>>input;

	string output;
	printKeypadOutput(input,output);


	return 0;
}
```

### ladder.cpp

```cpp
#include<iostream>
using namespace std;

//
int countWays(int n){
	//Base
	if(n<0){
		return 0;
	}
	if(n==0){
		return 1;
	}

	//Recursive	
	return countWays(n-1) + countWays(n-2) + countWays(n-3);

}


int main(){
	int n;
	cin>>n;
	cout <<countWays(n) <<endl;

	return 0;
}
```

## ./07 Linked Lists
### linked_list.cpp

```cpp
#include<iostream>
using namespace std;

class node{
public:
	int data;
	node* next;

	node(int data){
		this->data = data;
		next = NULL;
	}
};
//----------Linked List-----------//
void insertAtHead(node * &head,int data){
	if(head==NULL){
		head = new node(data);
		return;
	}	
	//otherwise 
	node * n = new node(data);
	n->next = head;
	head = n;
}

void insertInMiddle(node* &head, int data, int pos){
	if(pos==0){
		insertAtHead(head,data);
	}

	else{
		node * temp = head;
		for(int jump=1;jump<=pos-1;jump++){
			temp = temp->next;
		}

		node * n = new node(data);
		n->next = temp->next;
		temp->next = n;

	}
}

node* recReverse(node *head){
	//base case
	if(head==NULL or head->next==NULL){
		return head;
	}
	//otherwise
	node* sHead = recReverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return sHead;
}

void reverse(node *&head){
	node* prev = NULL;
	node* current = head;
	node * temp;

	while(current!=NULL){
		//store next
		temp = current->next;
		//update the current
		current->next = prev;

		//prev and current
		prev = current;
		current = temp;
	}

	head = prev;
	return;
}


node* kReverse(node *head,int k){
	//base case
	if(head==NULL){
		return NULL;
	}

	//reverse the first k nodes
	node* prev = NULL;
	node* current = head;
	node * temp;
	int cnt = 1;

	while(current!=NULL and cnt<=k){
		//store next
		temp = current->next;
		//update the current
		current->next = prev;

		//prev and current
		prev = current;
		current = temp;
		cnt++;
	}

	if(temp!=NULL){
		 head->next = kReverse(temp,k);
	}
	return prev;
}

node* merge(node *a, node* b){
	//Complete this method
	//base case
	if(a==NULL){
		return b;
	}
	if(b==NULL){
		return a;
	}

	//rec case
	node * c;

	if(a->data < b->data){
		c = a;
		c->next = merge(a->next,b);
	}
	else{
		c = b;
		c->next = merge(a,b->next);
	}
	return c;
}

node* midPoint(node *head){

	node * slow = head;
	node * fast = head->next;

	while(fast!=NULL and fast->next!=NULL){
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}


//ToDo : MergeSort
node* mergeSort(node * head){
	//base case
	if(head==NULL or head->next==NULL){
		return head;
	}

	//rec case
	node * mid = midPoint(head);

	//Break at the mid
	node * a = head;
	node * b = mid->next;
	mid->next = NULL;

	//Recursive Sort
	a = mergeSort(a);
	b = mergeSort(b);

	//Merge
	return merge(a,b);

}


void printLL(node * head){

	while(head!=NULL){
		cout <<head->data <<"-->";
		head = head->next;
	}
	cout <<endl;
}


int main(){
	node* a = NULL;
	insertAtHead(a,10);
	insertAtHead(a,7);
	insertAtHead(a,5);
	insertAtHead(a,1);
	insertAtHead(a,17);
	insertAtHead(a,2);
	insertAtHead(a,14);

	printLL(a);

	a = mergeSort(a);

	printLL(a);



	//1-> 5 -> 7 -> 10 -> NULL
	// 2 , 3, 6
	/*
	node* a = NULL;
	insertAtHead(a,10);
	insertAtHead(a,7);
	insertAtHead(a,5);
	insertAtHead(a,1);
	
	node* b = NULL;
	insertAtHead(b,6);
	insertAtHead(b,3);
	insertAtHead(b,2);

	node* head = merge(a,b);
	printLL(head);
	*/

	/*
	node* head = NULL;
	insertAtHead(head,4);
	insertAtHead(head,3);
	insertAtHead(head,2);
	insertAtHead(head,1);
	insertAtHead(head,0);
	printLL(head);
	head = kReverse(head,3);
	printLL(head);*/

	return 0;
}
```

## ./08 Stacks & Queue
### balanced_paranthesis.cpp

```cpp
#include<iostream>
#include<stack>
#include<string>
using namespace std;


bool isBalanced(string input){
	//Todo: Complete this method

	stack<char> s;
	for(auto ch : input){

		switch(ch){
			case '(':
			case '[':
			case '{': s.push(ch);
						break;

			case ')': if(!s.empty() and s.top()=='('){
						s.pop();
					  }
					  else{
					  	return false;
					  }
					  break;

			case ']': if(!s.empty() and s.top()=='['){
						s.pop();
					  }
					  else{
					  	return false;
					  }
					  break;

			case '}': if(!s.empty() and s.top()=='{'){
						s.pop();
					  }
					  else{
					  	return false;
					  }
					  break;
			default : continue;	  
		}
	}

	if(s.empty()==true){
		return true;
	}
	return false;
}



int main(){
	string s = "{ a + (b+c) + ([d+e]*f)) } + k`";//{ a + (b+c) + ([d+e]*f)) } + k";

	if(isBalanced(s)){
		cout<<"Balanced!"<<endl;
	}
	else{
		cout<<"Not Balanced "<<endl;

	}
return 0;
}
```

### first_non_repeating_queue.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

#include<iostream>
using namespace std;


void play_song(int song_id){
	
	if(song_id==0){
		return;
	}


}	


int main() {

	//First Non-Repeating character in the running stream
	queue<char> q;
	int freq[27] = {0}; //a-z

	char ch;
	cin >> ch;

	while(ch!='.'){

		//letter 
		q.push(ch);
		freq[ch - 'a']++;

		//query -> remove all chars from front of queue till you get a char with freq 1
		while(!q.empty()){
			int idx = q.front() - 'a';
			if(freq[idx]>1){
				q.pop();
			}
			else{
				cout<< q.front() <<endl;
				break;
			}
		}

		if(q.empty()){
			cout<<"-1" <<endl;
		}
		cin>>ch;
	}

	return 0;
}
```

### max_in_window_k.cpp

```cpp
#include <iostream>
#include<vector>
#include<deque>
using namespace std;

void maxSubArrayK(vector<int> a,int k){

    //Algorithm
    int n = a.size();

    deque<int> Q(k);
    //1. Process only the first K elements
    int i;

    for(i=0;i<k;i++){
        //Logic here ...

        while(!Q.empty() && a[i] > a[Q.back()]){
            Q.pop_back();
        }

        Q.push_back(i);

    }

    //2. Remaining the elements of the array
    for( ;i<n;i++){
        cout << a[Q.front()]<<" ";
        //Remove element from the left (contraction when an index lies outside the current window)
        while(!Q.empty() and Q.front() <=i-k){
            Q.pop_front();
        }
        while(!Q.empty() && a[i] >= a[Q.back()]){
            Q.pop_back();
        }

        //always
        Q.push_back(i);
    }


    cout<< a[Q.front()];

}

int main() {
    
    vector<int> arr{1,2,3,1,4,5,2,3,5};
    int k = 3;

    maxSubArrayK(arr,k);


    
    
    return 0;
}
```

### redundant_paranthesis.cpp

```cpp
#include<iostream>
#include<string>
#include<stack>
using namespace std;

bool checkRedundant(string str){
	//Complete
	stack<char> s;

	for(char ch : str){
		if(ch!=')'){
			s.push(ch); // a,b, + , - , ( ....
		}
		else{
			// ')'
			bool operator_found = false;

			while(!s.empty() and s.top()!='('){
				char top = s.top();
				if(top=='+' or top=='-' or top=='*' or top=='/'){
					operator_found = true;
				}
				s.pop();
			}
			s.pop(); //pop the opening bracked after the loop if over

			if(operator_found == false){
				return true;
			}
		}
	}
	return false;
}


int main() {
    string str = "((a+b)+c) + ((d*e))";
    if(checkRedundant(str)){
        cout<<"Contains Redundant Parenthesis";
    }
    else{
        cout<<"r";
    }
    return 0;
}

```

### simplify_path.cpp

```cpp
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

string simplifyPath(string path){
	//1. Step - Tokenisation & Filtering 

	istringstream iss(path);
	vector<string> tokens;

	string token;
	while(getline(iss,token,'/')){
		if(token=="." or token==""){
			continue;
		}
		tokens.push_back(token);
	}


	// 2. Handle .. 
	vector<string> stack; 

	if(path[0]=='/'){
		//denotes that our path is an abs path (wrt root dir)
		stack.push_back("");
	}

	for(string token : tokens){
		if(token==".."){
			//2 cases -> Abs path or relative path
			if(stack.size()==0 or stack[stack.size()-1]==".."){
				stack.push_back("..");
			}

			else if(stack[stack.size()-1]!=""){
				stack.pop_back();
			}
		}
		else{
			//x,y,z...
			stack.push_back(token);
		}

	}
	//single element
	if(stack.size()==1 and stack[0]==""){
		return "/";
	}

	//combine all elements in stack to get the answer
	ostringstream oss;
	int i = 0;

	for(auto token :stack){
		if(i!=0){
			oss<<"/";
		}
		i++;
		oss << token;
	}

	return oss.str();

}


int main(){
	string path = "/../x/y/../z/././w/a///../../c/./";
	//  Output :  /x/z/c
	cout << simplifyPath(path) <<endl;



	return 0;
}
```

## ./09 Binary Tree
### diameter.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}
/* Todo: Implement Level Order Traversal
Expected Output

1
2 3
4 5 6
7
*/

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}
//Helper Function : Height of the Tree
int height(node*root){
	if(root==NULL){
		return 0;
	}	
	int h1 = height(root->left);
	int h2 = height(root->right);
	return 1 + max(h1,h2);
}

// Diameter
// Time Complexity?
int diameter(node*root){
	//base case 
	if(root==NULL){
		return 0;
	}

	//rec case
	int D1 = height(root->left) + height(root->right);
	int D2 = diameter(root->left);
	int D3 = diameter(root->right);

	return max(D1,max(D2,D3));
}

//---------Diameter Optimised
class HDPair{
public:
	int height;
	int diameter;
};

HDPair optDiameter(node*root){
	HDPair p;

	if(root==NULL){
		p.height = p.diameter = 0;
		return p;
	}

	//otherwise
	HDPair Left = optDiameter(root->left);
	HDPair Right = optDiameter(root->right);

	p.height = max(Left.height,Right.height) + 1;

	int D1 = Left.height + Right.height;
	int D2 = Left.diameter;
	int D3 = Right.diameter;

	p.diameter = max(D1,max(D2,D3));
	return p;
}



int main(){
	
	node* root = buildTree();
	levelOrderPrint(root);
	cout << "Diameter is "<<diameter(root) <<endl;

	cout <<" Opt Diameter is " << optDiameter(root).diameter <<endl;


	return 0;
}
```

### height_balanced.cpp

```cpp
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}
//===============================
//ToDo:  Complete this Function |
//===============================

// O(N) time
pair<int,bool> isHeightBalanced(node *root){

	pair<int,bool> p, Left, Right;

	if(root==NULL){
		p.first = 0; //height
		p.second = true; // balanced
		return p;
	}

	//rec case (Postorder Traversal)
	Left = isHeightBalanced(root->left);
	Right = isHeightBalanced(root->right);

	int height = max(Left.first, Right.first) + 1;

	if(abs(Left.first - Right.first)<=1 and Left.second and Right.second){
			return make_pair(height,true);
	}
	return make_pair(height,false);
}



int main(){
	
	node* root = new node(1);
	root->left = new node(2);
	root->right = new node(3);
	root->left->left = new node(4);
	root->left->right = new node(5);
	root->right->right = new node(6);
	root->left->right->left = new node(7);
	root->left->right->right = new node(8);
	//root->left->right->right->left = new node(9);
	//root->left->right->right->right = new node(10);
	
	pair<int,bool> p = isHeightBalanced(root);
	if(p.second){
		cout << "Yes, its height balanced";
	}
	else{
		cout << "Not a height balanced tree";
	}


	return 0;
}
```

### level_order_build.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}
/*Level Order Traversal
Expected Output

1
2 3
4 5 6
7
*/

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}

/* Implement Level Order Build
for the tree
*/

node* levelOrderBuild(){

	int d;
	cin>>d;

	node* root = new node(d);

	queue<node*> q;
	q.push(root);


	while(!q.empty()){
		node* current = q.front();
		q.pop();

		int c1, c2;
		cin>> c1 >> c2;

		if(c1!=-1){
			current->left = new node(c1);
			q.push(current->left);
		}
		if(c2!=-1){
			current->right = new node(c2);
			q.push(current->right);
		}
	}
	return root;
}

//Todo: Replace with Descendant Sum leaving leaf nodes intact
int replaceWithSum(node *root){
	//base case
	if(root==NULL){
		return 0;
	}
	if(root->left==NULL and root->right==NULL){
		return root->data;
	}
	//recursive case
	int LS = replaceWithSum(root->left);
	int RS = replaceWithSum(root->right);

	int temp = root->data;
	root->data = LS + RS;
	return root->data + temp;
}

int main(){
	
	//node* root = buildTree();
	node* root = levelOrderBuild();
	levelOrderPrint(root);
	cout<<endl;
	replaceWithSum(root);
	levelOrderPrint(root);


	return 0;
}
```

### level_order_traversal.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}
/* Todo: Implement Level Order Traversal
Expected Output

1
2 3
4 5 6
7
*/

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}




int main(){
	
	node* root = buildTree();
	levelOrderPrint(root);


	return 0;
}
```

### max_subset.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}
//ToDo : Complete the MaxSubset Function

class Pair{
public:
	int inc;
	int exc;

};
//O(N)
Pair maxSubsetSum(node* root){
	Pair p;
	if(root==NULL){
		p.inc = p.exc = 0;
		return p;
	}

	Pair Left = maxSubsetSum(root->left);
	Pair Right = maxSubsetSum(root->right);

	p.inc = root->data + Left.exc + Right.exc;
	p.exc = max(Left.inc,Left.exc) + max(Right.inc,Right.exc);

	return p;
}


int main(){
	
	node* root = buildTree();
	levelOrderPrint(root);

	Pair p = maxSubsetSum(root);
	cout <<"Max Sum : "<< max(p.inc, p.exc) <<endl;


	return 0;
}
```

### node_at_kth_distance.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}
//===============================
//ToDo:  Complete this Function |
//===============================
void printAtLevelK(node*root, int k){
	if(root==NULL){
		return;
	}
	if(k==0){
		cout<<root->data<<" ";
		return;
	}
	printAtLevelK(root->left,k-1);
	printAtLevelK(root->right,k-1);
	return;
}


int printNodesAtDistanceK(node* root, node* target,int k){

	//base case
	if(root==NULL){
		return -1;
	}

	//reach the target node
	if(root==target){
		printAtLevelK(target,k);
		return 0;
	}


	//other case
	int DL = printNodesAtDistanceK(root->left,target,k);
	if(DL!=-1){

		//2 cases
		// Print the current node
		if(DL + 1 ==k){
			cout << root->data;
		}
		// or print somenodes in the rightsubtree
		else{
			printAtLevelK(root->right,k-2-DL);
		}
		return 1 + DL;
	}
	int DR = printNodesAtDistanceK(root->right,target,k);
	if(DR!=-1){
		//2 cases
		//print current node
		if(DR + 1 ==k){
			cout<< root->data <<" ";
		}
		else{
			printAtLevelK(root->left,k-2-DR);
		}
		return 1 + DR;
	}
	return -1;
}

int main(){
	
	node* root = new node(1);
	root->left = new node(2);
	root->right = new node(3);
	root->left->left = new node(4);
	root->left->right = new node(5);
	root->right->right = new node(6);
	root->left->right->left = new node(7);
	root->left->right->right = new node(8);
	root->left->right->right->left = new node(9);
	root->left->right->right->right = new node(10);
	
	//Target Node 5
	node* target = root->left->right;
	

	int k = 2;	
	printNodesAtDistanceK(root,target,k);
	cout<<endl;


	return 0;
}
```

### root_2_leaft_paths.cpp

```cpp
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}
//===============================
//ToDo:  Complete this Function |
//===============================
void printRoot2LeafPaths(node* root, vector<int> &path){
	
	if(root==NULL){
		return;
	}
	//end at leaft node, print the path
	if(root->left==NULL and root->right==NULL){
		for(int data:path){
			cout<<data<<"->";
		}
		cout << root->data <<" ";
		cout<<endl;
		return;
	}
	path.push_back(root->data);
	printRoot2LeafPaths(root->left,path);
	printRoot2LeafPaths(root->right,path);
	path.pop_back();
	return;
}

int main(){
	
	node* root = new node(1);
	root->left = new node(2);
	root->right = new node(3);
	root->left->left = new node(4);
	root->left->right = new node(5);
	root->right->right = new node(6);
	root->left->right->left = new node(7);
	root->left->right->right = new node(8);
	root->left->right->right->left = new node(9);
	root->left->right->right->right = new node(10);
	

	vector<int> temp;
	printRoot2LeafPaths(root,temp);



	return 0;
}
```

### tree_input.cpp

```cpp
1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
```

### vertical_print.cpp

```cpp
#include<iostream>
#include<queue>
#include<vector>
#include<map>
using namespace std;

class node{

public:
	int data;
	node*left;
	node*right;
	
	node(int d){
		data = d;
		left = NULL;
		right = NULL;
	}
};

//Input : 1 2 4 -1 -1 5 7 -1 -1 -1 3 -1 6 -1 -1
node* buildTree(){

	int d;
	cin>>d;

	if(d==-1){
		return NULL;
	}

	node* n = new node(d);
	n->left = buildTree();
	n->right = buildTree();

	return n;
}

void levelOrderPrint(node*root){

	queue<node*> q;
	q.push(root);
	q.push(NULL);

	while(!q.empty()){
		node* temp = q.front();
		if(temp==NULL){
			cout<<endl;
			q.pop();
			//insert a new null for the next level
			if(!q.empty()){
				q.push(NULL);
			}
		}
		else{
			q.pop();
			cout<<temp->data<<" ";

			if(temp->left){
				q.push(temp->left);
			}
			if(temp->right){
				q.push(temp->right);
			}
		}

	}
	return;
}
//===============================
//ToDo:  Complete this Function |
//===============================

//helper
void traverseTree(node*root, int d, map<int,vector<int> > &m){
	if(root==NULL){
		return;
	}

	m[d].push_back(root->data);
	traverseTree(root->left, d-1,m);
	traverseTree(root->right,d+1,m);
}

void verticalOrderPrint(node* root){
		
	map<int, vector<int> > m;
	int d = 0;

	traverseTree(root, d, m);

	//Keys are sorted (-2, -1,0,1,2,3.....)
	for(auto p:m){
		int key = p.first;
		vector<int> line = p.second;

		for(auto data : line){
			cout << data <<" ";
		}
		cout <<endl;

	}	
	return;
}

int main(){
	
	node* root = new node(1);
	root->left = new node(2);
    root->right = new node(3);
    root->left->left = new node(4);
    root->left->right = new node(5);
    root->right->left = new node(6);
    root->right->right = new node(7);
    root->right->left->right = new node(8);
    root->right->right->right = new node(9);

    verticalOrderPrint(root);


	return 0;
}
```

## ./10 BST
### bst.cpp

```cpp
#include <iostream>
using namespace std;

class Node
{
  public:
   int key;
   Node *left;
   Node *right;

   Node(int key){
       this->key = key;
       left = right  = NULL;
   }
};

Node* insert(Node * root, int key){
	if(root==NULL){
		return new Node(key);
	}

	//rec case 
	if(key < root->key){
		root->left = insert(root->left,key);
	}
	else{
		root->right = insert(root->right,key);
	}
	return root;

}

bool search(Node * root, int key){
	//Homework
	


}

void printInOrder(Node *root){
	if(root==NULL){
		return;
	}
	//left, root, right
	printInOrder(root->left);
	cout << root-> key <<" ,";
	printInOrder(root->right);
}


int main(){

	Node * root = NULL;
	int arr[] = {8,3,10,1,6,14,4,7,13};

	for(int x : arr){
		root = insert(root,x);
	}
	printInOrder(root);

	return 0;
}
```

### bst_2_linked_list.cpp

```cpp
//BST to Linked List
#include <iostream>
using namespace std;

class Node
{
  public:
   int key;
   Node *left;
   Node *right;

   Node(int key){
       this->key = key;
       left = right  = NULL;
   }
};

Node* insert(Node * root, int key){
	if(root==NULL){
		return new Node(key);
	}

	//rec case 
	if(key < root->key){
		root->left = insert(root->left,key);
	}
	else{
		root->right = insert(root->right,key);
	}
	return root;

}



void printInOrder(Node *root){
	if(root==NULL){
		return;
	}
	//left, root, right
	printInOrder(root->left);
	cout << root-> key <<" ,";
	printInOrder(root->right);
}


//---------BST to Sorted Linked List
class LinkedList{
public:
	Node * head;
	Node * tail;
};

LinkedList tree2LL(Node * root){

	LinkedList l;
	//base case
	if(root==NULL){
		l.head = l.tail = NULL;
		return l;
	}

	//4 cases
	if(root->left==NULL and root->right==NULL){
		l.head = l.tail = root;
	}
	else if(root->left!=NULL and root->right==NULL){
		LinkedList leftLL = tree2LL(root->left);
		leftLL.tail->right = root;

		l.head = leftLL.head;
		l.tail = root;
	}
	else if(root->left==NULL and root->right!=NULL){
		LinkedList rightLL = tree2LL(root->right);
		root->right = rightLL.head;

		l.head = root;
		l.tail = rightLL.tail;

	}
	else{
		LinkedList leftLL = tree2LL(root->left);
		LinkedList rightLL = tree2LL(root->right);
		leftLL.tail->right = root;
		root->right = rightLL.head;

		l.head = leftLL.head;
		l.tail = rightLL.tail;
	}

	return l;
}



int main(){

	Node * root = NULL;
	int arr[] = {8,3,10,1,6,14,4,7,13};

	for(int x : arr){
		root = insert(root,x);
	}
	//printInOrder(root);
	LinkedList l = tree2LL(root);

	Node * temp = l.head;
	while(temp!=NULL){
		cout << temp->key <<"--> ";
		temp = temp->right;
	}
	

	return 0;
}
```

### closest_in_bst.cpp

```cpp
#include <iostream>
using namespace std;

class Node
{
  public:
   int key;
   Node *left;
   Node *right;

   Node(int key){
       this->key = key;
       left = right  = NULL;
   }
};

Node* insert(Node * root, int key){
	if(root==NULL){
		return new Node(key);
	}

	//rec case 
	if(key < root->key){
		root->left = insert(root->left,key);
	}
	else{
		root->right = insert(root->right,key);
	}
	return root;

}

int findClosestInBST(Node * root, int target){
	//todo 

	int closest;
	int diff = INT_MAX;

	Node *temp = root;

	while(temp!=NULL){

		int current_diff = abs(temp->key - target);

		if(current_diff==0){
			return temp->key;
		}

		
		if(current_diff < diff){
			diff = current_diff;
			closest = temp->key;
		}


		//right or left
		if(temp-> key < target){
			temp = temp -> right;
		}
		else{
			temp = temp->left;
		}
	}
	return closest;

}

void printInOrder(Node *root){
	if(root==NULL){
		return;
	}
	//left, root, right
	printInOrder(root->left);
	cout << root-> key <<" ,";
	printInOrder(root->right);
}


int main(){

	Node * root = NULL;
	int arr[] = {8,3,10,1,6,14,4,7,13};

	for(int x : arr){
		root = insert(root,x);
	}
	//printInOrder(root);

	cout << findClosestInBST(root,12) <<endl;

	return 0;
}
```

### inorder_succcessor.cpp

```cpp
//BST to Linked List
#include <iostream>
using namespace std;

class Node
{
  public:
   int key;
   Node *left;
   Node *right;

   Node(int key){
       this->key = key;
       left = right  = NULL;
   }
};

Node* insert(Node * root, int key){
	if(root==NULL){
		return new Node(key);
	}

	//rec case 
	if(key < root->key){
		root->left = insert(root->left,key);
	}
	else{
		root->right = insert(root->right,key);
	}
	return root;

}



void printInOrder(Node *root){
	if(root==NULL){
		return;
	}
	//left, root, right
	printInOrder(root->left);
	cout << root-> key <<" ,";
	printInOrder(root->right);
}


//---------Next Inorder Successor

Node * inorderSucc(Node * root, Node * target){

	// If Right Subtree 
	if(target->right!=NULL){
		Node* temp = target->right;
		while(temp->left!=NULL){
			temp = temp->left;
		}
		return temp;
	}


	// Otherwise 
	Node * temp = root;
	Node * succ = NULL;

	while (temp!=NULL){

		if(temp->key > target->key){
			succ = temp;
			temp = temp->left;
		}
		else if(temp->key < target->key ){
			temp = temp->right;
		}
		else{
			break;
		}
	}
	return succ;
}


int main(){

	Node * root = NULL;
	root = insert(root,8);
	root = insert(root,3);
	root = insert(root,10);
	root = insert(root,1);
	root = insert(root,6);
	root = insert(root,14);
	root = insert(root,4);
	root = insert(root,7);
	root = insert(root,13);

	//Test our Code
	Node* t1 = root->left->right->right;
	Node* t2 = root->right;

	cout<<"Inorder succ of 7 is" << inorderSucc(root,t1)->key <<endl;
	cout<<"Inorder succ of 10 is" << inorderSucc(root,t2)->key <<endl;
 


	return 0;
}
```

## ./11 Heaps
### 03_merge_k_sorted.cpp

```cpp
#include <iostream>
#include<vector>
#include<queue>
using namespace std;

vector<int> mergeKArrays(vector<vector<int> > arrays){
    //logic  
  
    int k = arrays.size();
    //triplet -> element, array idx, element idx
    priority_queue< vector<int> , vector<vector<int> > , greater<vector<int> > > q;


    vector<int> output;

    //init the heap 
    for(int i=0;i<k;i++){
        int element = arrays[i][0];
        q.push({element,i,0});
    }

    //start popping & pushing more elements
    while(!q.empty()){

        auto top = q.top();
        q.pop();

        int element = top[0];
        int a_idx = top[1];
        int e_idx = top[2];


        output.push_back(element);

        if(e_idx + 1 < arrays[a_idx].size()){
            int next_element = arrays[a_idx][e_idx+1];
            q.push({next_element,a_idx,e_idx+1});
        }

    }




    return output;
}

int main() {
    

    vector<vector<int> > arr = {{10,15,20,30},
                                {2,5,8,14,24},
                                {0,11,60,90}};

    //various approaches 
    vector<int> result = mergeKArrays(arr);
    

    //output
    for(auto x:result){
        cout<<x <<" ";
    }


    return 0;
}

```

### 04_running_median.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;


//Running Median Heaps
int main(){



	priority_queue<int> leftheap; //maxheap
	priority_queue<int,vector<int>,greater<int> > rightheap; //min heap

	int d;
	cin>>d;
	leftheap.push(d);

	float med = d;
	cout<< med <<" ";

	cin>>d;
	while(d!=-1){
		//left or right or equal
		if(leftheap.size() > rightheap.size()){
			if(d < med){
				rightheap.push(leftheap.top());
				leftheap.pop();
				leftheap.push(d);
			}
			else{
				rightheap.push(d);
			}
			med = (leftheap.top() + rightheap.top())/2.0;
		}
		else if(leftheap.size()==rightheap.size()){
			if(d < med){
				leftheap.push(d);
				med = leftheap.top();
			}
			else{
				rightheap.push(d);
				med = rightheap.top();
			}

		}
		else{
			if(d < med){
				leftheap.push(d);
			}
			else{
				leftheap.push(rightheap.top());
				rightheap.pop();
				rightheap.push(d);
			}
			med = (leftheap.top() + rightheap.top())/2;

		}

		cout<< med<<" ";
		cin>>d;
	}



	return 0;
}
```

### cars_input.cpp

```cpp
5 3
C1 1 1
C2 2 1
C3 3 2
C4 0 1
C5 2 3


```

### custom_compare.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

class Compare{
public:
	bool operator()(int a,int b){
		return a < b;
	}
};


int main(){

	int arr[] = {10,15,20,13,6,90};
	int n = sizeof(arr)/sizeof(int);

	priority_queue<int, vector<int> , Compare >  heap;

	for(int x : arr){
		heap.push(x);
	}

	while(!heap.empty()){
		cout << heap.top() <<endl;
		heap.pop(); 
	}




	return 0;
}
```

### heaps_01_cabs.cpp

```cpp
#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

class Car{

public:
	string id;
	int x,y;
	Car(string id,int x,int y){
		this->id = id;
		this->x = x;
		this->y = y;
	}
	int dist() const{
		return x*x + y*y; //square of the dist
	}
};

class CarCompare{
public:
	bool operator()(const Car A,const Car B){
		return A.dist() < B.dist();// max heap
	}
};



void printNearestCars(vector<Car> cars,int k){


	//create a max heap of size K 
	priority_queue<Car, vector<Car> , CarCompare> max_heap(cars.begin(), cars.begin() + k);

	//remaining cars
	for(int i=k; i < cars.size();i++){
		auto car = cars[i];

		if(car.dist() < max_heap.top().dist()){
			max_heap.pop(); //remove the root node largest
			max_heap.push(car);
		}
	}	

	//print all the cars inside the heap they will be smallest
	vector<Car> output;
	while(!max_heap.empty()){
		//cout<< max_heap.top().id <<endl;
		output.push_back(max_heap.top());
		max_heap.pop();
	}

	//vector of k nearest cars
	reverse(output.begin(),output.end());

	for(auto car : output){
		cout << car.id <<endl;
	}

	return;

}


int main(){


	int N,K;
	cin>>N>>K;

	string id;
	int x,y;

	vector<Car> cars;

	for(int i=0;i<N;i++){
		cin>> id>>x>>y;
		Car car(id,x,y);
		cars.push_back(car);
	}

	printNearestCars(cars,K);

	return 0;
}
```

### heaps_02_ropes.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;

int join_ropes(int ropes[], int n) {

	//min heap
	priority_queue<int,vector<int> , greater<int> > pq(ropes,ropes+n);


	//logic
	int cost = 0;

	while(pq.size() > 1){

		int A = pq.top();
		pq.pop();

		int B = pq.top();
		pq.pop();


		int new_rope = (A+B);
		cost  += new_rope;
		pq.push(new_rope);

	}

	return cost;

}

int main() {
	int ropes[] = {4, 3, 2, 6};
	int n = 4;

	cout << join_ropes(ropes, n) << endl;




	return 0;
}
```

### sorting_using_heap.cpp

```cpp
#include<iostream>
#include<queue>
using namespace std;


int main(){

	int arr[] = {10,15,20,13,6,90};
	int n = sizeof(arr)/sizeof(int);

	priority_queue<int, vector<int> , greater<int> >  heap;

	for(int x : arr){
		heap.push(x);
	}

	while(!heap.empty()){
		cout << heap.top() <<endl;
		heap.pop(); 
	}




	return 0;
}
```

## ./12 Hashing/Counting Rectangles
### rectangle.cpp

```cpp
#include<iostream>
#include<vector>
#include<set>
using namespace std;

//Point Class
class Point {
public:
	int x;
	int y;

	Point() {

	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

};

//Comparator Class
class Compare{

public:
	bool operator()(const Point p1,const Point p2){
		if(p1.x==p2.x){
			return p1.y < p2.y;
		}
		return p1.x < p2.x;
	}
};


//Count Rectangles Function
int count_rectangles(vector<Point> points) {

	//1. Insert all Points in the set
	set<Point,Compare> s;

	for(Point p:points){
		s.insert(p);
	}

	int ans = 0;
	//2. Logic Brute Force Two Points + LookUp for other Two
	for(auto it = s.begin();it!= prev(s.end());it++){
		for(auto jt= next(it); jt!=s.end();jt++){

			Point p1 = *it;
			Point p2 = *jt;

			//small check that we want to make
			if(p2.x==p1.x or p2.y==p1.y){
				continue;
			}


			//P3, P4
			Point p3(p1.x,p2.y);
			Point p4(p2.x,p1.y);

			//Lookup
			if(s.find(p3)!=s.end() and s.find(p4)!=s.end())
			{
				ans += 1;
			}

		}

	}

	return ans/2;

}



int main() {

	int N;
	cin >> N;

	int x, y;

	vector<Point> points;

	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		Point p(x, y);
		points.push_back(p);
	}

	cout << count_rectangles(points) << endl;

	return 0;
}



```

## ./12 Hashing/Counting Triangles
### triangles.cpp

```cpp
#include <iostream>
#include<vector>
#include<unordered_map>
using namespace std;

int count_triangles(vector<pair<int,int> > &points){

    unordered_map<int,int> freq_x;
    unordered_map<int,int> freq_y;

    //Count the freq by iterating over all the points
    for(auto p:points){
        int x = p.first;
        int y = p.second;
        freq_x[x]++;
        freq_y[y]++;
    } 


    //count 
    int count = 0;
    for(auto p:points){
        int x = p.first;
        int y = p.second;

        int fx = freq_x[x];
        int fy = freq_y[y];

        count += (fx-1)*(fy-1);
    }
    return count;

}


int main() {
    
    int N;
    cin>>N;

    vector<pair<int,int> > points;

    for(int i=0;i<N;i++){
        int x,y;
        cin>>x>>y;
        points.push_back({x,y});
    }
    cout<<count_triangles(points) <<endl;

    return 0;
}

```

## ./12 Hashing
### anagrams_substrings.cpp

```cpp
#include<iostream>
#include<map>
#include<vector>
using namespace std;

/*
1. Generate all substrings
2. Generate their hash
3. Hash the 'hash' values to club all anagrams in single bucket, to get their frequency count
4. From freq count, we can easily count the paris  
*/
vector<int> getHashValue(string s,int i,int j){

	vector<int> freq(26,0);

	//iterate over the original string from i to j to fill this vector
	for(int k=i;k<=j;k++){
		char ch = s[k];
		freq[ch-'a']++;
	}

	return freq;

}



int anagrams_substrings(string s){

	map<vector<int> , int > m;

	for(int i=0;i<s.length();i++){
		for(int j=i; j<s.length();j++){

			//Substring S[i...j]
			vector<int> h = getHashValue(s,i,j);
			//put it inside a map
			m[h]++;
		}
	}

	//pairs
	int ans = 0;
	for(auto p : m){

		int freq = p.second;
		if(freq>=2){
			ans += (freq)*(freq-1)/2;
		}

	}
	return ans;

}



int main(){

	string s;
	cin>>s ;

	cout<<anagrams_substrings(s)<<endl;


	return 0;
}
```

### quick-brown-fox.cpp

```cpp
#include <iostream>
#include<unordered_set>
#include<climits>
using namespace std;


string s ="thequickbrownfoxjumpsoverthehighbridge";

string words[] = {"the","fox","thequickbrownfox", "jumps","lazy","lazyfox",

					"highbridge","the","over", "bridge","high","tall",

					"quick","brown"};

/*
string s ="thequickbrownfox";

string words[] = {"the", "quickbrown", "fox","quick","brown"};
*/
//Main Logic
int min_bars_helper(string s,string words[],int idx, unordered_set<string> &m){

	//base case
	if(s[idx]=='\0'){
		return 0;
	}

	//rec case
	int ans = INT_MAX;
	string current_string = "";

	for(int j=idx; s[j]!='\0';j++){
		current_string += s[j];

		//at every step you can whether this prefix is present in set 
		if(m.find(current_string)!=m.end()){
			int remaning_ans = min_bars_helper(s,words,j+1,m);
			if(remaning_ans!=-1){
				ans = min(ans, 1 + remaning_ans);

			}
		}
	}

	if(ans==INT_MAX){
		return -1;
	}
	return ans;
}



int min_bars(){

	unordered_set<string> m;

	for(string w:words){
		m.insert(w);
	}

	//recursive helper function 
	int output = min_bars_helper(s,words,0,m);
	return output - 1;

}

int main(){

	cout<< min_bars() <<endl;

	return 0;
}


```

### triplets_in_gp.cpp

```cpp
#include <iostream>
#include<unordered_map>
#include<vector>
using namespace std;

int count_triplets(vector<int> arr,int r){

    int n = arr.size();
    unordered_map<long,long> right,left;

    //Init the Right Map with freq, Left map = 0
    for(auto x : arr){
        right[x]++;
        left[x] = 0;
    }

    //compute by iterating left to right
    int ans = 0;
    for(int i = 0; i < n; i++){

        right[arr[i]]--;

        if(arr[i]%r==0){
            long b = arr[i];
            long a = arr[i]/r;
            long c = arr[i]*r;

            ans += left[a] * right[c];
        }

        left[arr[i]]++;

    }    
    return ans;

}

int main() {
    
    int n,r;
    cin>>n>>r;
    vector<int> arr(n,0);

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    cout<<count_triplets(arr,r);

    return 0;
}

```

## ./13 Tries
### little_cute_cat_trie.cpp

```cpp
#include<iostream>
#include<unordered_map>
#include<cstring>
#include<vector>
using namespace std;

//Build a Prefix Tree - Trie
class Node{
public:
	char data;
	unordered_map<char,Node*> children;
	bool isTerminal;

	Node(char d){
		data = d;
		isTerminal = false;
	}
};

class Trie{
public:
	Node*root;

	Trie(){
		root = new Node('\0');
	}

	void insert(string word){

		Node* temp = root;

		for(char ch : word){

			if(temp->children.count(ch)==0){
				Node *n = new Node(ch);
				temp->children[ch] = n;
			}
			temp = temp->children[ch];
		}

		temp->isTerminal = true;
	}
};

void searchHelper(Trie t, string document, int i, unordered_map<string,bool> &m ){

		Node*temp = t.root;
		for(int j = i; j < document.length();j++){
			char ch = document[j];
			if(temp->children.count(ch)==0){
				return;
			}
			temp = temp->children[ch];
			if(temp->isTerminal){
				//history part 
				string out = document.substr(i,j-i+1);
				m[out] = true;
			}

		}
		return;

}

void documentSearch(string document, vector<string> words){

	//1. Create a trie of words
	Trie t;
	for(string w : words){
		t.insert(w);
	}
	
	//2. Searching (Helper Fn)
	unordered_map<string,bool> m;
	for(int i=0;i<document.length();i++){
		searchHelper(t, document, i, m);
	}

	//3. You can check which words are marked as True inside Hashmap
	for(auto w :words){
		if(m[w]){
			cout<<w <<" : True" <<endl;
		}
		else{
			cout<<w <<" : False "<<endl;
		}
	}

	return;
}


int main(){
	
    string document  ="little cute cat loves to code in c++, java & python";
    vector<string> words{"cute cat", "ttle", "cat","quick","big"};

    documentSearch(document,words);


	return 0;
}


```

### max_xor_trie.cpp

```cpp
#include<iostream>
using namespace std;


class node{
public:
	node *left; //0
	node *right; // 1
};

class trie{
	node*root;

public:
	trie(){
		root = new node();
	}

	void insert(int n){
		//bits of that number in the trie
		node* temp = root;
		for(int i=31;i>=0;i--){
			int bit = (n>>i)&1;
			if(bit==0){
				if(temp->left==NULL){
					temp->left = new node();
				}
				//go to that node
				temp = temp->left;
			}
			else{
				if(temp->right==NULL){
					temp->right = new node();
				}
				temp = temp->right;
			}
		}
		//Insertion is Done
	}

	int max_xor_helper(int value){

		int current_ans = 0;
		node* temp = root;

		for(int j=31;j>=0;j--){
			int bit =(value>>j)&1;

			if(bit==0){
				//find the opp value
				if(temp->right!=NULL){
					temp = temp->right;
					current_ans += (1<<j);
				}
				else{
					temp = temp->left;
				}
			}
			else{
				//look for a zero 
				if(temp->left!=NULL){
					temp = temp->left;
					current_ans += (1<<j);
				}
				else{
					temp = temp->right;
				}
			}

		}
		return current_ans;

	}
	int max_xor(int *input,int n){

		int max_xor = 0;
		for(int i=0;i<n;i++){
			int value = input[i];
			insert(value);
			int current_xor = max_xor_helper(value);
			max_xor = max(max_xor,current_xor);
		}

		return max_xor;
	}

};


int main(){

	int input[] = {3,10,5,25,9,2};
	int n = sizeof(input)/sizeof(int);
	trie t;
	cout<< t.max_xor(input,n)<<endl;




	return 0;

};
```

### suffix_trie.cpp

```cpp
#include<iostream>
#include<unordered_map>
#include<cstring>
using namespace std;


//Build a Prefix Tree - Trie
class Node{
public:
	char data;
	unordered_map<char,Node*> m;
	bool isTerminal;

	Node(char d){
		data = d;
		isTerminal = false;
	}
};


class SuffixTrie{

	Node*root;
public:
	SuffixTrie(){
		root = new Node('\0');
	}

	//later
	void insert_helper(string word){

		Node* temp = root;

		for(char ch : word){

			if(temp->m.count(ch)==0){
				Node *n = new Node(ch);
				temp->m[ch] = n;
			}
			temp = temp->m[ch];
		}

		temp->isTerminal = true;

	}

	bool search(string word){

		Node*temp = root;

		for(char ch : word){

			if(temp->m.count(ch)==0){
				return false;
			}
			temp = temp->m[ch];


		}
		return temp->isTerminal;
	}

	void insert(string word){
		//pick all substrings from (i, eos) and insert_helper
		for(int i=0;word[i]!='\0';i++){
			insert_helper(word.substr(i));
		}
	}
};


int main(){

		//Simplified Suffix Trie
		string input = "hello";
		string suffixes[] = {"lo","ell","hello"};

		SuffixTrie t;
		t.insert(input);

		for(auto sf : suffixes){
			if(t.search(sf)){
				cout<<"yes ";
			}
			else{
				cout<<"no ";
			}
		}

		return 0;
}


```

### trie_introduction.cpp

```cpp
#include<iostream>
#include<unordered_map>
using namespace std;


//Build a Prefix Tree - Trie
class Node{
public:
	char data;
	unordered_map<char,Node*> m;
	bool isTerminal;

	Node(char d){
		data = d;
		isTerminal = false;
	}
};


class Trie{

	Node*root;
public:
	Trie(){
		root = new Node('\0');
	}

	//later
	void insert(string word){

		Node* temp = root;

		for(char ch : word){

			if(temp->m.count(ch)==0){
				Node *n = new Node(ch);
				temp->m[ch] = n;
			}
			temp = temp->m[ch];
		}

		temp->isTerminal = true;

	}

	bool search(string word){

		Node*temp = root;

		for(char ch : word){

			if(temp->m.count(ch)==0){
				return false;
			}
			temp = temp->m[ch];


		}
		return temp->isTerminal;
	}
};


int main(){

		string input = "this is a suffix trie";

		string queries[] = "fix,"


		return 0;
}


```

## ./14  Graphs
### 01_adj_list.cpp

```cpp
#include<iostream>
#include<list>
using namespace std;


class Graph{

	int V;
	list<int> *l;

public:
	Graph(int v){
		V = v;
		l = new list<int>[V];
	}

	void addEdge(int i,int j,bool undir=true){
		l[i].push_back(j);
		if(undir){
			l[j].push_back(i);
		}
	}

	void printAdjList(){
		//Iterate over all the rows
		for(int i=0;i<V;i++){
			cout<<i<<"-->";
			//every element of ith linked list
			for(auto node:l[i]){
				cout << node <<",";
			}
			cout <<endl;

		}


	}

};

int main(){
	Graph g(6);
	g.addEdge(0,1);
	g.addEdge(0,4);
	g.addEdge(2,1);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.printAdjList();
	return 0;
}









```

### 02_adj_list.cpp

```cpp
#include<iostream>
#include<list>
#include<unordered_map>
#include<vector>
using namespace std;


class Node{
public:
	string name;
	list<string> nbrs;

	Node(string name){
		this->name = name;
	}
};

class Graph{
	unordered_map<string,Node*> m;

public:
	Graph(vector<string> cities){
		for(auto city : cities){
			m[city] = new Node(city);
		}
	}

	void addEdge(string x,string y,bool undir=false){
		m[x]->nbrs.push_back(y);

		if(undir){
			m[y]->nbrs.push_back(x);
		}
	}

	void printAdjList(){
		for(auto cityPair : m){
			auto city = cityPair.first;
			Node *node = cityPair.second;
			cout<<city<<"-->";
			for(auto nbr : node->nbrs){
				cout << nbr<<",";
			}
			cout<<endl;
		}
	}
};

int main(){
	vector<string> cities = {"Delhi","London","Paris","New York"};
	Graph g(cities);

	g.addEdge("Delhi","London");
	g.addEdge("New York","London");
	g.addEdge("Delhi","Paris");
	g.addEdge("Paris","New York");

	g.printAdjList();
	

	return 0;
}




```

### 02_adj_list_node.cpp

```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<unordered_map>
#include<list>
using namespace std;


class Node{
public:
	string name;
	list<string> nbrs;

	Node(string name){
		this->name = name;
	}
};

class Graph{
	//Node Name -- Pointer to Node Object
	unordered_map<string,Node*> m;
public:
	Graph(vector<string> cities){
		for(auto city : cities){
			m[city] = new Node(city);
		}
	}

	void addEdge(string x,string y,bool undir=false){
		m[x]->nbrs.push_back(y);
		if(undir){
			m[y]->nbrs.push_back(x);
		}
	}

	void printAdjList(){
		for(auto cityPair : m){
			auto city = cityPair.first;
			cout<<city<<"-->";
			Node *node = cityPair.second;
			for(auto nbr : node->nbrs){
				cout<<nbr<<",";
			}
			cout<<endl;
		}
	}
};


int main(){
	vector<string> cities = {"Delhi","London","Paris","New York"};
	Graph g(cities);
	g.addEdge("Delhi","London");
	g.addEdge("New York","London");
	g.addEdge("Delhi","Paris");
	g.addEdge("Paris","New York");

	g.printAdjList();
	

	return 0;
}
```

### 03_bfs_.cpp

```cpp
#include<iostream>
#include<list>
#include<queue>
using namespace std;


class Graph{

	int V;
	list<int> *l;

public:
	Graph(int v){
		V = v;
		l = new list<int>[V];
	}

	void addEdge(int i,int j,bool undir=true){
		l[i].push_back(j);
		if(undir){
			l[j].push_back(i);
		}
	}
	void bfs(int source){

		queue<int> q;
		bool *visited = new bool[V]{0};

		q.push(source);
		visited[source] = true;

		while(!q.empty()){
			//Do some work for every node
			int f = q.front();
			cout<<f <<endl;
			q.pop();

			//PUsh the nbrs of current node inside q if they are not already visited
			for(auto nbr : l[f]){
				if(!visited[nbr]){
					q.push(nbr);
					visited[nbr] = true;
				}
			}
		}
	}
	
	

};

int main(){
	Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(5,6);
	g.addEdge(4,5);
	g.addEdge(0,4);
	g.addEdge(3,4);
	g.bfs(1);
	return 0;
}









```

### 03_bfs_shortest_path.cpp

```cpp
#include<iostream>
#include<list>
#include<queue>
using namespace std;


class Graph{

	int V;
	list<int> *l;

public:
	Graph(int v){
		V = v;
		l = new list<int>[V];
	}

	void addEdge(int i,int j,bool undir=true){
		l[i].push_back(j);
		if(undir){
			l[j].push_back(i);
		}
	}
	void bfs(int source,int dest=-1){

		queue<int> q;
		bool *visited = new bool[V]{0};
		int *dist = new int[V]{0};
		int *parent = new int[V];

		for(int i=0;i<V;i++){
			parent[i] = -1;
		}

		q.push(source);
		visited[source] = true;
		parent[source] = source;
		dist[source] = 0;

		while(!q.empty()){
			//Do some work for every node
			int f = q.front();
			//cout<<f <<endl;
			q.pop();

			//PUsh the nbrs of current node inside q if they are not already visited
			for(auto nbr : l[f]){
				if(!visited[nbr]){
					q.push(nbr);
					//parent and dist
					parent[nbr] = f;
					dist[nbr] = dist[f] + 1;
					visited[nbr] = true;
				}
			}
		}
		//print the shortest distance
		for(int i=0;i<V;i++){
			cout<<"Shortest dist to "<<i<<" is "<<dist[i] <<endl;
		}


		//print the path from a source to any dest
		if(dest!=-1){
			int temp = dest;
			while(temp!=source){
				cout<<temp<<"-- ";
				temp = parent[temp];
			}
			cout<<source<<endl;
		}

	}
	
	

};

int main(){
	Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(5,6);
	g.addEdge(4,5);
	g.addEdge(0,4);
	g.addEdge(3,4);
	g.bfs(1,6);
	return 0;
}
```

### 04_dfs.cpp

```cpp
#include<iostream>
#include<list>
#include<queue>
using namespace std;


class Graph{

	int V;
	list<int> *l;

public:
	Graph(int v){
		V = v;
		l = new list<int>[V];
	}

	void addEdge(int i,int j,bool undir=true){
		l[i].push_back(j);
		if(undir){
			l[j].push_back(i);
		}
	}
	void dfsHelper(int node,bool *visited){
		visited[node] = true;
		cout<<node<<",";

		//make a dfs call on all its unvisited neighbours
		for(int nbr : l[node]){
			if(!visited[nbr]){
				dfsHelper(nbr,visited);
			}
		}
		return;

	}

	void dfs(int source){
		bool *visited = new bool[V]{0};
		dfsHelper(source,visited);
	}
};

int main(){
	Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(5,6);
	g.addEdge(4,5);
	g.addEdge(0,4);
	g.addEdge(3,4);
	g.dfs(1);
	return 0;
}
```

### board-game.cpp

```cpp
#include <iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;

#define M 3 
#define N 4 


class Node{
public:
	char s;
	unordered_map<char,Node*> children;
	string word;
	bool isTerminal;

	Node(char s){
		this->s = s;
		isTerminal = false;
		word = "";
	}
};

class Trie{
public:
	Node*root;

	Trie(){
		root = new Node('\0');
	}

	void addWord(string word){

		Node * temp = root;
		for(auto ch : word){
			if(temp->children.count(ch)==0){
				temp->children[ch] = new Node(ch);
			}
			temp = temp->children[ch];
		}
		//last node
		temp->isTerminal = true;
		temp->word = word;
	}
};


//main algorithm (8-way dfs + trie guided search)

void dfs(char board[M][N],Node *node,int i,int j,bool visited[][N], unordered_set<string> &output){

	//base case
	char ch = board[i][j];
	if(node->children.count(ch)==0){
		return;
	}

	//otherwise trie contains this node
	visited[i][j] = true;
	node = node->children[ch];


	// if it is a terminal node in the trie 
	if(node->isTerminal){
		output.insert(node->word);
	}

	//explore the neigbours 
    int dx[] = {0, 1 , 1 ,1, 0, -1, -1,-1};
	int dy[] = {-1,-1, 0, 1, 1, 1, 0, -1};

	for(int k=0;k<8;k++){

		int ni = i + dx[k];
		int nj = j + dy[k];

		//if it is in bounds and is not visited
		if(ni>=0 and nj>=0 and ni < M and nj < N and !visited[ni][nj]){
			dfs(board,node,ni,nj,visited,output);
		}
	}
	//last step (backtracking)
	visited[i][j] = false;
	return;
}


int main() {
    

    
    string words[] = {"SNAKE", "FOR", "QUEZ", "SNACK", "SNACKS", "GO","TUNES","CAT"};
    
    char board[M][N] = { { 'S', 'E', 'R' ,'T'}, 
                          { 'U', 'N', 'K' ,'S'},
                          { 'T', 'C', 'A' ,'T'} };

     //1. Trie

      Trie t;
      for(auto w : words){
      	t.addWord(w);
      }

      //2. Take a container to store words that are found in dfs search
      unordered_set<string> output;


      //3. Step (8-DFS Search from every cell)
      bool visited[M][N] =  {0};


      for(int i=0; i<M;i++){
      	for(int j=0;j<N;j++){
      		dfs(board,t.root,i,j,visited,output);
      		//reset the visited array after every call (while backtracking)
      	}
      }

      //4. Print the Output

      for(auto word: output){
      	cout<< word <<endl;
      }


    return 0;
}

```

### cycle_detection_directed.cpp

```cpp
#include<iostream>
#include<list>
#include<vector>
using namespace std;

class Graph{
	list<int> *l;
	int V;

public:
	Graph(int V){
		this->V = V;
		l = new list<int>[V];
	}

	void addEdge(int x,int y){
		l[x].push_back(y);
	}

	bool dfs(int node,vector<bool> &visited, vector<bool> &stack){
		//arrive at node
		visited[node] = true;
		stack[node] = true;

		//do some work at node,return true if backedge is found here itself
		for(int nbr : l[node]){

			if(stack[nbr]==true){
				return true;
			}
			else if(visited[nbr]==false){
				bool nbrFoundACycle = dfs(nbr,visited,stack);
				if(nbrFoundACycle){
					return true;
				}
			}
		}

		//going back
		stack[node] = false;
		return false;
	}

	bool contains_cycle(){
		vector<bool> visited(V,false);
		vector<bool> stack(V,false);

		for(int i=0;i<V;i++){
			if(!visited[i]){
				if(dfs(i,visited,stack)){
					return true;
				}
			}

		}
		return false;
	}

};

//Udemy Code Judge - Stub
bool contains_cycle(int V,vector<pair<int,int> > edges){
    //Complete this method

	Graph g(V);
	for(auto edge : edges){
		g.addEdge(edge.first,edge.second);
	}
	return g.contains_cycle();
    
}

int main(){

	Graph g(3);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,0);

	cout << g.contains_cycle() <<endl;

	return 0;
}
```

### cycle_detection_undirected.cpp

```cpp
#include<iostream>
#include<list>
#include<vector>
using namespace std;

class Graph{
	list<int> *l;
	int V;

public:
	Graph(int V){
		this->V = V;
		l = new list<int>[V];
	}

	//undirected graph
	void addEdge(int x,int y){
		l[x].push_back(y);
		l[y].push_back(x);
	}
	bool dfs(int node, vector<bool> &visited, int parent){
		//mark that node visited
		visited[node] = true;

		for(auto nbr : l[node]){

			if(!visited[nbr]){

				bool nbrFoundACycle = dfs(nbr,visited,node);
				if(nbrFoundACycle){
					return true;
				}
			}
			//nbr is visited and its not the parent of current node in the current dfs call
			else if(nbr!=parent){
				return true;
			}
		}
		return false;
	}

	bool contains_cycle(){
		//Graph is single component
		vector<bool> visited(V,false);
		return dfs(0, visited, -1);
	}

};

bool contains_cycle(int V,vector<pair<int,int> > edges){
    //Complete this method

    Graph g(V);
    for(auto edge:edges){
    	g.addEdge(edge.first,edge.second);
    }
    return g.contains_cycle();
    
}

int main(){

	Graph g(3);
	g.addEdge(0,1);
	g.addEdge(1,2);
	//g.addEdge(2,0);

	cout << g.contains_cycle() <<endl;
	return 0;
}
```

### dijkstra.cpp

```cpp
#include<iostream>
#include<list>
#include<set>
#include<vector>
#include<climits>
using namespace std;

class Graph{

	int V;
	list<pair<int,int> > *l;

public:
	Graph(int v){
		V = v;
		l = new list<pair<int,int> >[V];
	}

	void addEdge(int u,int v,int wt,bool undir = true){

		l[u].push_back({wt,v});
		if(undir){
			l[v].push_back({wt,u});
		}
	}

	int dijkstra(int src,int dest){

		//Data Structures
		vector<int> dist(V,INT_MAX);
		set<pair<int,int> >  s;

		//1. Init 
		dist[src] = 0;
		s.insert({0,src});

		while(!s.empty()){

			auto it = s.begin();
			int node = it->second;
			int distTillNow = it->first; 
			s.erase(it); //Pop 

			//Iterate over the nbrs of node
			for(auto nbrPair : l[node]){
				//......

				int nbr = nbrPair.second;
				int currentEdge = nbrPair.first;

				if(distTillNow + currentEdge < dist[nbr]){
					//remove if nbr already exist in the set

					auto f = s.find({dist[nbr],nbr});
					if(f!=s.end()){
						s.erase(f);
					}
					//insert the updated value with the new dist
					dist[nbr] = distTillNow + currentEdge;
					s.insert({dist[nbr],nbr});

				}

			}

		}
		//Single Source Shortest Dist to all other nodes
		for(int i=0;i<V;i++){
			cout<<"Node i "<<i <<" Dist "<<dist[i] <<endl;
		}
		return dist[dest];

	}

};

int main(){

	Graph g(5);
	g.addEdge(0,1,1);
	g.addEdge(1,2,1);
	g.addEdge(0,2,4);
	g.addEdge(0,3,7);
	g.addEdge(3,2,2);
	g.addEdge(3,4,3);

	cout << g.dijkstra(0,4)<<endl;
}
```

### largest_island copy.cpp

```cpp
#include<iostream>
#include <vector>
using namespace std;

int dfs(vector<vector<int> > &matrix, vector<vector<bool> > &visited, int i,int j,int m,int n){

	visited[i][j] = true;

	int cs = 1; 

	int dx[] = {1,-1,0,0};
	int dy[] = {0,0,1,-1};

	for(int k=0;k<4;k++){
		int nx = i + dx[k];
		int ny = j  + dy[k];

		if(nx>=0 and nx<m and ny>=0 and ny<n and matrix[nx][ny]==1 and !visited[nx][ny]){
			int subcomponent = dfs(matrix,visited,nx,ny,m,n);
			cs += subcomponent;
		}
	}
	return cs;
}


int largest_island(vector<vector<int> > matrix){
    //return the size of largest island in grid
    int m = matrix.size();
    int n = matrix[0].size();

    //visited matrix
    vector<vector<bool> > visited(m, vector<bool>(n,false));

    int largest = 0;

    for(int i=0;i<m;i++){
    	for(int j=0;j<n;j++){
    		if(!visited[i][j] and matrix[i][j]==1){

    			int size = dfs(matrix,visited,i,j,m,n);
    			if(size>largest){
    				largest = size;
    			}

    		}

    	}
    }    
    return largest;
}


int main(){
    vector<vector<int> > grid = {
                            {1, 0, 0, 1, 0},
                            {1, 0, 1, 0, 0},
                            {0, 0, 1, 0, 1},
                            {1, 0, 1, 1, 1},
                            {1, 0, 1, 1, 0}
                            };
    
    cout<< largest_island(grid) <<endl;


    return 0;
}

```

### largest_island.cpp

```cpp
#include<iostream>
#include <vector>
using namespace std;

int dfs(vector<vector<int> > &matrix, vector<vector<bool> > &visited, int i,int j,int m,int n){

	visited[i][j] = true;

	int cs = 1; 

	int dx[] = {1,-1,0,0};
	int dy[] = {0,0,1,-1};

	for(int k=0;k<4;k++){
		int nx = i + dx[k];
		int ny = j  + dy[k];

		if(nx>=0 and nx<m and ny>=0 and ny<n and matrix[nx][ny]==1 and !visited[nx][ny]){
			int subcomponent = dfs(matrix,visited,nx,ny,m,n);
			cs += subcomponent;
		}
	}
	return cs;
}


int largest_island(vector<vector<int> > matrix){
    //return the size of largest island in grid
    int m = matrix.size();
    int n = matrix[0].size();

    //visited matrix
    vector<vector<bool> > visited(m, vector<bool>(n,false));

    int largest = 0;

    for(int i=0;i<m;i++){
    	for(int j=0;j<n;j++){
    		if(!visited[i][j] and matrix[i][j]==1){

    			int size = dfs(matrix,visited,i,j,m,n);
    			if(size>largest){
    				largest = size;
    			}

    		}

    	}
    }    
    return largest;
}


int main(){
    vector<vector<int> > grid = {
                            {1, 0, 0, 1, 0},
                            {1, 0, 1, 0, 0},
                            {0, 0, 1, 0, 1},
                            {1, 0, 1, 1, 1},
                            {1, 0, 1, 1, 0}
                            };
    
    cout<< largest_island(grid) <<endl;


    return 0;
}

```

### shortest_grid_path.cpp

```cpp
#include<iostream>
#include<vector>
#include<set>
using namespace std;

class Node{
public:
	int x;
	int y;
	int dist;

	Node(int x,int y,int dist){
		this-> x = x;
		this->y = y;
		this->dist = dist;
	}
};

//comparator should return boolean value, 
// indicating whether the element passed as 
// first argument is considered to go before the second in the specific strict weak ordering
class Compare{
public:
	bool operator()(const Node &a,const Node &b){
		return a.dist <= b.dist;
	}
};


int shortest_path(vector<vector<int> > grid){
    //return the shortest path len
    
    int m = grid.size();
    int n = grid[0].size();

    int i = 0;
    int j = 0;

    //2D vector to denote of each cell
    vector<vector<int> > dist(m+1, vector<int>(n+1,INT_MAX));

    dist[i][j] = grid[0][0];
    set<Node,Compare> s;

    s.insert(Node(0,0,dist[0][0]));

    int dx[] = {0,0,1,-1};
    int dy[] = {1,-1,0,0};


    while(!s.empty()){

    	auto it = s.begin();
    	int cx = it->x;
    	int cy = it->y;
    	int cd = it->dist;
    	s.erase(it);

    	//update nbrs
    	for(int k=0;k<4;k++){
    		int nx = cx + dx[k];
    		int ny = cy + dy[k];

    		if(nx>=0 and nx<m and ny>=0 and ny<n and cd + grid[nx][ny] < dist[nx][ny]){
    			//remove the old node if it exist
    			Node temp(nx,ny,dist[nx][ny]);
    			if(s.find(temp)!=s.end()){
    				s.erase(s.find(temp));
    			}

    			//insert the new node in the set
    			int nd = grid[nx][ny] + cd;
    			dist[nx][ny] = nd;
    			s.insert(Node(nx,ny,nd));
    		}

    	}

    }
    return dist[m-1][n-1];
    
}

int main(){

	return 0;
}
```

### weighted_graph.cpp

```cpp
#include<iostream>
#include<list>
#include<set>
using namespace std;

class Graph{

	int V;
	list<pair<int,int> > *l;

public:
	Graph(int v){
		V = v;
		l = new list<pair<int,int> >[V];
	}

	void addEdge(int u,int v,int wt,bool undir = true){

		l[u].push_back({wt,v});
		if(undir){
			l[v].push_back({wt,u});
		}
	}

};

int main(){

	Graph g(5);
	g.addEdge(0,1,1);
	g.addEdge(1,2,2);
	g.addEdge(0,2,4);
	g.addEdge(0,3,7);
	g.addEdge(3,2,2);
	g.addEdge(3,4,3);




}
```

## ./15 DP1
### frog_jumps.cpp

```cpp
CODING INTERVIEW ~ 20 mins

FROG JUMPS
============
Given an array containing integers, and there is a frog 
sitting at the starting of the array. Each integer represents the 
maximum number of steps frog can take in the array.
Write a function which can calculates the minimum jumps 
required by frog to reach the end of the array.



```

### lcs.cpp

```cpp
#include<iostream>
#include<vector>
using namespace std;


int lcs(string s1,string s2,int i,int j,vector<vector<int> > &dp){
	//base case
	if(i==s1.length() or j==s2.length()){
		return  0;
	}
	//check if a state is already computed
	if(dp[i][j]!=-1){
		return dp[i][j];
	}

	//rec case
	if(s1[i]==s2[i]){
		return dp[i][j] = 1 + lcs(s1,s2,i+1,j+1,dp);
	}

	int op1 = lcs(s1,s2,i+1,j,dp);
	int op2 = lcs(s1,s2,i,j+1,dp);
	return dp[i][j] = max(op1,op2);
}

int main(){

	string s1 = "ABCD";
	string s2 = "ABEDG";

	int n1 = s1.length();
	int n2 = s2.length();

	vector<vector<int> > dp(n1+1, vector<int>(n2+1,-1)); //n1 X n2 

	cout<< lcs(s1,s2,0,0,dp) <<endl;


	for(int i=0;i<=n1;i++){
		for(int j=0;j<=n2;j++){
			cout<<dp[i][j]<<" ";
		}
		cout<<endl;
	}

	return 0;
}
```

### lcs_bottom_up.cpp

```cpp
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;


int lcs(string s1,string s2){
	//bottom up approach to lcs
	int n1 = s1.length();
	int n2 = s2.length();

	//2d dp array
	vector<vector<int > > dp(n1 + 1, vector<int>(n2+1,0));

	//1,1 ... n1,n2
	for(int i=1;i<=n1;i++){
		for(int j=1;j<=n2;j++){

			if(s1[i-1]==s2[j-1]){
				dp[i][j] = 1 + dp[i-1][j-1];
			}
			else{
				int op1 = dp[i-1][j];
				int op2 = dp[i][j-1];
				dp[i][j] = max(op1,op2);
			}
		}
	}

	//print
	/*
	for(int i=0;i<=n1;i++){
		for(int j=0;j<=n2;j++){
			cout<<dp[i][j]<<" ";
		}
		cout<<endl;
	}
	*/

	vector<char> result;
	int i=n1,j=n2;
	while(i!=0 and j!=0){
		if(dp[i][j]==dp[i][j-1]){
			j--;
		}
		else if(dp[i][j]==dp[i-1][j]){
			i--;
		}
		else{
			result.push_back(s1[i-1]);
			i--;
			j--;
		}
	}
	reverse(result.begin(),result.end());
	for(char x:result){
		cout<<x <<",";
	}

	return dp[n1][n2];

}

int main(){

	string s1 = "ABCD";
	string s2 = "ABEDG";

	cout<<endl;
	cout <<lcs(s2,s1) <<endl;


	

	return 0;
}
```

### rod_cutting.cpp

```cpp
#include<iostream>
using namespace std;


//Recursive Solution
int max_profit(int prices[],int n){
	//base case
	if(n<=0){
		return 0;
	}

	//rec case
	int ans = INT_MIN;

	for(int i=0;i < n;i++){
		int cut = i + 1;

		int current_ans = prices[i] + max_profit(prices,n - cut);
		ans = max(ans,current_ans);

	}
	return ans;
}



//bottom up solution
int max_profit_dp(int *prices,int n){

	int dp[n+1];
	dp[0] = 0;


	for(int len=1;len<=n;len++){

		int ans = INT_MIN;
		for(int i=0;i<len;i++){
			int cut = i + 1;
			int current_ans = prices[i] + dp[len - cut];
			ans = max(current_ans,ans);
		}
		//computed the ans for dp[len]
		dp[len] = ans;

	}

	return dp[n];
}


int main(){

	int prices[] = {1, 5, 8, 9, 10, 17, 17, 20};
	int n = sizeof(prices)/sizeof(int);

	cout<< max_profit_dp(prices,n)<<endl;


	return 0;
}
```

## ./17 LRU
### LRU.cpp

```cpp
#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data (Linked List)
class Node{
public:
	string key;
	int value;
	Node(string key,int value){
		this->key = key;
		this->value = value;
	}
};


//LRU Cache Data Structure
class LRUCache{
public:
	int maxSize;
	list<Node> l;
	unordered_map<string,list<Node>::iterator > m;

	LRUCache(int maxSize){
		this->maxSize = maxSize > 1 ? maxSize : 1;
	}

	void insertKeyValue(string key,int value){
		//2 cases
		if(m.count(key)!=0){
			//replace the old value and update
			auto it = m[key];
			it-> value = value;
		}
		else{
			//check if cache if full or not
			//remove the least recently used item from cache
			if(l.size()==maxSize){
				Node last = l.back();
				m.erase(last.key); //remove from hashmap
				l.pop_back(); //remove from linked list
			}

			Node n(key,value);
			l.push_front(n);
			m[key] = l.begin();
		}
	}

	int* getValue(string key){
			
		if(m.count(key)!=0){
			auto it = m[key];

			int value = it->value;
			l.push_front(*it);
			l.erase(it);
			m[key] = l.begin();
			return &l.begin()->value;
		}	
		return NULL;

	}

	string mostRecentKey(){
		return l.front().key;
	}

};


int main(){
	LRUCache lru(3);
	lru.insertKeyValue("mango",10);
	lru.insertKeyValue("apple",20);
	lru.insertKeyValue("guava",30);
	cout << lru.mostRecentKey() <<endl;

	lru.insertKeyValue("mango",40);
	cout << lru.mostRecentKey() <<endl;

	int *orders = lru.getValue("mango");
	if(orders!=NULL){
		cout<<"Order of Mango "<<*orders <<endl;
	}


	lru.insertKeyValue("banana",20);

	if(lru.getValue("apple")==NULL){
		cout<<"apple doesn't exist";
	}

	if(lru.getValue("guava")==NULL){
		cout<<"guava doesn't exist";
	}

	if(lru.getValue("banana")==NULL){
		cout<<"banana doesn't exist";
	}
	if(lru.getValue("mango")==NULL){
		cout<<"mango doesn't exist";
	}

	

	return 0;
}	
```

