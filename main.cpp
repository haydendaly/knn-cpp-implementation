#include <iostream>
#include <set>
#include <math.h> // pow(base,exponent)
#include <vector>

using namespace std;

float euclidean_distance(vector<int> base_tensor, vector<int> comparing_tensor)
{ // Euclidean distance for N dimensional input tensor
    if (base_tensor.size() != comparing_tensor.size())
    {
        return rand() % 100; // Tensors must be same length. Otherwise return random num.
    }

    float distance = 0.0;
    for (int i = 0; i < base_tensor.size(); i++)
    { // (p1-q1)^2 + (p2-q2)^2 + . . . + (pi-qi)^2 + (pn-qn)^2
        distance += pow(base_tensor[i] - comparing_tensor[i], 2);
    }
    distance = sqrt(distance); // sqrt( (pn-qn)^2 )

    return distance;
}

struct VectorDistance
{ 
    // VectorDistance data type that stores tensor and distance from a base tensor
    float distance;
    vector<int> tensor;

    // Constructor
    VectorDistance(vector<int> base_tensor, vector<int> tensor_)
    {
        // Call euclidean distance function to calculate distance property
        distance = euclidean_distance(base_tensor, tensor_);
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
