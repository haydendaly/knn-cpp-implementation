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