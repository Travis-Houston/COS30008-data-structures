#include "Polygon.h"
#include <stdexcept>

using namespace std;

// Constructor
Polygon::Polygon() 
{
    fNumberOfVertices = 0;
}

// Get the number of vertices in the polygon
size_t Polygon::getNumberOfVertices() const 
{
    return fNumberOfVertices;
}

// Get a specific vertex of the polygon by index
const Vector2D& Polygon::getVertex( size_t aIndex ) const 
{
    // Check if the index is within the bounds of the array
    if ( aIndex < fNumberOfVertices )
    {
        return fVertices[aIndex];
    }
    
    // Throw an exception if the index is out of range
    throw out_of_range( "Illegal index value." );
}

// Read the data of the polygon from an input stream
void Polygon::readData( istream& aIStream )
{
    // Read vertices from the input stream until it fails or ends
    while ( aIStream >> fVertices[fNumberOfVertices] )
    {
        fNumberOfVertices++;
    }
}

// Calculate the perimeter of the polygon
float Polygon::getPerimeter() const
{
    float Result = 0.0f;

    // Check if the polygon has more than 2 vertices
    if ( fNumberOfVertices > 2 )
    {
        // Calculate the sum of the lengths of all edges
        for ( size_t i = 1; i < fNumberOfVertices; i++ )
        {
            Result += (fVertices[i] - fVertices[i - 1]).length();
        }

        // Add the length of the last edge connecting the last and first vertices
        Result += (fVertices[0] - fVertices[fNumberOfVertices - 1]).length();
    }

    return Result;
}

// Scale the polygon by a scalar value
Polygon Polygon::scale( float aScalar ) const
{
    // Create a copy of the current polygon
    Polygon Result = *this;
    
    // Scale each vertex by the scalar value
    for ( size_t i = 0; i < fNumberOfVertices; i++ )
    {
        Result.fVertices[i] = fVertices[i] * aScalar;
    }
    
    return Result;
}

float Polygon::getSignedArea() const {
    float area = 0.0f;

    // Apply the Shoelace formula
    for (size_t i = 0; i < fNumberOfVertices; i++) {
        const Vector2D& currentVertex = fVertices[i];
        const Vector2D& nextVertex = fVertices[(i + 1) % fNumberOfVertices];
        area += (currentVertex.getX() * nextVertex.getY()) - (currentVertex.getY() * nextVertex.getX());
    }

    // Divide the final result by 2 to get the signed area
    area /= 2.0f;

    return area;
}