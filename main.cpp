#include <iostream>
#include <set>
#include <math.h> // pow(base,exponent)
#include <vector>

using namespace std;

float cosine_similarity(vector<int> base_tensor, vector<int> comparing_tensor)
{
    // Init values for dot product and magnitudes
    float dot = 0.0, base_magnitude = 0.0, comparing_magnitude = 0.0;
    for (int i = 0; i < base_tensor.size(); i++)
    {
        // Calculate dot product of the two vectors
        dot += base_tensor[i] * comparing_tensor[i];
        // Equivalent to sigmoid of all elements squared
        base_magnitude += pow(base_tensor[i], 2);
        comparing_magnitude += pow(comparing_tensor[i], 2);
    }
    return dot / (sqrt(base_magnitude) * sqrt(comparing_magnitude));
}

struct VectorDistance
{
    // VectorDistance data type that stores tensor and distance from a base tensor
    float distance;
    vector<int> tensor;

    // Constructor
    VectorDistance(vector<int> base_tensor, vector<int> tensor_)
    {
        // Call distance function to calculate distance property
        distance = cosine_similarity(base_tensor, tensor_);
        tensor = tensor_;
    }

    // Destructor
    ~VectorDistance()
    {
        distance = 0;
        tensor.clear();
    }

    // Comparison operator
    friend bool operator<(VectorDistance a, VectorDistance b)
    {
        return a.distance > b.distance;
    }
};

vector<vector<int>> get_neighbors(vector<vector<int>> train, vector<int> base_tensor, int k)
{
    // Create temporary set to store VectorDistance data
    set<VectorDistance> tensors;
    for (vector<int> tensor : train)
    {
        // Create VectorDistance data points using base_tensor and comparing tensor
        VectorDistance temp_tensor = VectorDistance(base_tensor, tensor);
        // Insert new distance/tensor pair into set
        tensors.insert(temp_tensor);
        if (tensors.size() > k)
        {
            // If set of nearest vectors is larger than specified value k, delete one with largest euclidean distance
            set<VectorDistance>::iterator i = tensors.end();
            tensors.erase(--i);
        }
    }
    // Translate set into vector output and return value (C++ 11 only!)
    vector<vector<int>> result;
    for (VectorDistance f : tensors)
    {
        result.push_back(f.tensor);
    }
    return result;
}

vector<vector<int>> generate_sample_data(int amount, int dimensions)
{
    /*
        Sample Tensor Array 

        t111, t121, t131     t112, t122, t132     t113, t123, t133
        t211, t221, t231     t212, t222, t232     t213, t223, t233
        t311, t321, t331     t312, t322, t332     t313, t323, t333
    */
    vector<vector<int>> test_tensors(amount, vector<int>(dimensions, 0));
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            test_tensors[i][j] = rand() % 100;
        }
    }
    return test_tensors;
}

int main()
{
    // Create 1000 vectors of size 20
    vector<vector<int>> data = generate_sample_data(1000, 20);
    // Run KNN algorithm for 10 nearest neighbors
    vector<vector<int>> result = get_neighbors(data, data[0], 10);

    // Print resulting nearest neighbors
    for (auto f : result)
    {
        for (auto h : f)
        {
            cout << h << ", ";
        }
        cout << "\n";
    }
}
