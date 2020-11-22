#include <iostream>
#include <set>
#include <vector>

using namespace std;

float euclidean_distance(vector<int> base_tensor, vector<int> base_tensor_2) {
    // James - For N dimensional input tensor
    float random_num = rand() % 100;
    return random_num;
}

struct VectorDistance {
    float distance;
    vector<int> tensor;

    VectorDistance(vector<int> base_tensor, vector<int> tensor_) {
        distance = euclidean_distance(base_tensor, tensor_);
        tensor = tensor_;
    }

    friend bool operator<(VectorDistance a, VectorDistance b) {
        return a.distance > b.distance;
    }
};

vector<vector<int>> get_neighbors(vector<vector<int>> train, vector<int> base_tensor, int k) {
    set<VectorDistance> tensors;
    for (vector<int> tensor : train) {
        VectorDistance temp_tensor = VectorDistance(base_tensor, tensor);
        tensors.insert(temp_tensor);
        if (tensors.size() > k) {
            set<VectorDistance>::iterator i = tensors.end();
            tensors.erase(--i);
        }
    }
    vector<vector<int>> result;
    for (VectorDistance f : tensors) {
        result.push_back(f.tensor);
    }
    return result;
}

vector<vector<int>> generate_sample_data(int amount, int dimensions) {
    /*
        Sample Tensor Array 

        t111, t121, t131     t112, t122, t132     t113, t123, t133
        t211, t221, t231     t212, t222, t232     t213, t223, t233
        t311, t321, t331     t312, t322, t332     t313, t323, t333
    */ 
    vector<vector<int>> test_tensors(amount, vector<int> (dimensions, 0)); 
    for (int i = 0; i < amount; i++){
        for(int j = 0; j < dimensions; j++){
            test_tensors[i][j] = rand() % 100;
        }
    }
    return test_tensors; 
}

int main() {
    vector<vector<int>> data = generate_sample_data(15, 10);
    vector<vector<int>> result = get_neighbors(data, data[0], 2);
    for (auto f : result) {
        for (auto h : f) {
            cout << h << ", ";
        }
        cout << "\n";
    }
}
