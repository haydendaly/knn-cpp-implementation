#include <iostream>
#include <set>
#include <vector>

using namespace std;

float euclidean_distance(vector<int> base_tensor, vector<int> base_tensor_2) {
    // James - For N dimensional input tensor
    float random_num = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
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
}

vector<vector<int>> get_neighbors (vector<vector<int>> train, vector<int> base_tensor, int k) {
    // Hayden
    set<VectorDistance> tensors;
    for (vector<int> tensor : train) {
        VectorDistance temp_tensor = VectorDistance(base_tensor, tensor);
        tensors.insert(temp_tensor);
    }
    for (auto f : tensors) {
        cout << f.distance << '\n';
    }
    // Return smallest k VectorDistance in set
    return train;
}

vector<vector<int>> generate_sample_data(int amount, int dimensions) {
    // Roman - Create amount of sample tensors of dimension provided
    /*
        Sample Tensor Array 

        t111, t121, t131     t112, t122, t132     t113, t123, t133
        t211, t221, t231     t212, t222, t232     t213, t223, t233
        t311, t321, t331     t312, t322, t332     t313, t323, t333
    */ 
    
    vector<vector<int>> test_tensors; 
    for (int i = 0; i < amount; i++){
        for(int j = 0; j < dimensions; j++){
            test_tensors[i][j] = rand() % 100;
            std::cout <<  test_tensors[i][j]; 
        }
        std::cout << "\n"; 
    }
    return test_tensors; 
}

int main() {
    vector<vector<int>> data = generate_sample_data(15,10);
    vector<vector<int>> result = get_neighbors(data, data[0], 5);
}
