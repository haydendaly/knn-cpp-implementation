#include <iostream>
#include <set>

using namespace std;

float euclidean_distance(vector<int> base_tensor, vector<int> base_tensor) {
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

vector<vector<int>> get_neighbors(vector<vector<int>> train, vector<int> base_tensor, int k) {
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
}

int main() {
    vector<vector<int>> data = generate_sample_data();
    vector<vector<int>> result = get_neighbors(data, data[0], 5);
}
