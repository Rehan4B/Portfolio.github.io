#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <ctime>
#include <algorithm> // Include this header file for the reverse function
using namespace std;

// Data structure to represent a docking station
struct DockingStation {
    int id;
    string name;
    int capacity;
    int availableBikes;
};

// Data structure to represent a graph edge
struct Edge {
    int destination;

    int weight;
};

// Data structure to represent a user
struct User {
    string username;
    string password;
    vector<string> invoices;
    vector<string> feedback;
};

// Array to store docking station data
DockingStation stations[10];
int stationCount = 3;

// Adjacency list to store the graph
map<int, vector<Edge>> graph;

// Vector to store registered users
vector<User> users;

// Current logged-in user
User* loggedInUser = nullptr;

// Function prototypes
void registerUser();
bool loginUser();
void logoutUser();
void viewDockingStations();
void rentBike();
void returnBike();
void showRentalPrice();
void viewInvoices();
void saveInvoices();
void addInvoice(int stationId, int bikes, double price);
void leaveFeedback();
void viewFeedback();
void addStation();
void removeStation();
void adminMenu();
void generateDailyReport();
void simulateActivity();
void displayMenu();
void findShortestPath();

// Function to update availability
void updateAvailability(int stationId, int bikes)
 {
    if (stationId >= 0 && stationId < stationCount)
        {
        stations[stationId].availableBikes += bikes;
        if (stations[stationId].availableBikes > stations[stationId].capacity)
         {
            stations[stationId].availableBikes = stations[stationId].capacity;
        }
        else if (stations[stationId].availableBikes < 0)
         {
            stations[stationId].availableBikes = 0;
        }
        cout << "Updated bikes at " << stations[stationId].name << ": " << stations[stationId].availableBikes << endl;
    }
    else
        {
        cout << "Error: Station ID not found." << endl;
    }
}

// Constant pricing function
double getPrice()
 {
    const double constantPrice = 10.0;
    return constantPrice;
}

// Function to register a new user
void registerUser()
 {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    for (const auto& user : users)
        {
        if (user.username == username)
         {
            cout << "Username already exists. Please try again." << endl;
            return;
        }
    }

    users.push_back({username, password, {}, {}});
    cout << "Registration successful!" << endl;
}

// Function to authenticate a user
bool loginUser()
 {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    for (auto& user : users)
        {
        if (user.username == username && user.password == password)
         {
            loggedInUser = &user;
            cout << "Login successful! Welcome, " << username << "." << endl;
            return true;
        }
    }

    cout << "Invalid username or password. Please try again." << endl;
    return false;
}

// Function to log out the current user
void logoutUser()
 {
    if (loggedInUser)
        {
        cout << "Goodbye, " << loggedInUser->username << "!" << endl;
        loggedInUser = nullptr;
    }
    else
        {
        cout << "No user is currently logged in." << endl;
    }
}

// Function to save invoices to a file
void saveInvoices()
 {
    if (!loggedInUser)
        {
        cout << "You need to be logged in to save invoices." << endl;
        return;
    }

    ofstream file(loggedInUser->username + "_invoices.txt");
    if (!file)
        {
        cout << "Error saving invoices." << endl;
        return;
    }

    for (const auto& invoice : loggedInUser->invoices)
        {
        file << invoice << endl;
    }

    file.close();
    cout << "Invoices saved successfully to " << loggedInUser->username << "_invoices.txt" << endl;
}

// Function to add an invoice
void addInvoice(int stationId, int bikes, double price)
 {
    if (!loggedInUser)
        {
        cout << "You need to be logged in to perform this action." << endl;
        return;
    }

    string invoice = "Rented " + to_string(bikes) + " bikes from " + stations[stationId].name + ". Total cost: $" + to_string(price);
    loggedInUser->invoices.push_back(invoice);
    cout << "Invoice added: " << invoice << endl;
}

// Function to view user invoices
void viewInvoices()
 {
    if (!loggedInUser)
        {
        cout << "You need to be logged in to view invoices." << endl;
        return;
    }

    if (loggedInUser->invoices.empty())
        {
        cout << "No invoices found." << endl;
        return;
    }

    cout << "Invoices for " << loggedInUser->username << ":" << endl;
    for (const auto& invoice : loggedInUser->invoices)
        {
        cout << "- " << invoice << endl;
    }
}

// Function to leave feedback
void leaveFeedback()
 {
    if (!loggedInUser)
        {
        cout << "You need to be logged in to leave feedback." << endl;
        return;
    }

    string feedback;
    cout << "Enter your feedback: ";
    cin.ignore();
    getline(cin, feedback);

    loggedInUser->feedback.push_back(feedback);
    cout << "Thank you for your feedback!" << endl;
}

// Function to view all feedback
void viewFeedback()
 {
    cout << "\nUser Feedback:" << endl;
    for (const auto& user : users)
        {
        if (!user.feedback.empty())
         {
            cout << "Feedback from " << user.username << ":" << endl;
            for (const auto& fb : user.feedback)
             {
                cout << "- " << fb << endl;
            }
        }
    }
}

// Function to add a new docking station
void addStation()
 {
    if (stationCount >= 10)
        {
        cout << "Cannot add more stations. Maximum limit reached." << endl;
        return;
    }

    string name;
    int capacity;
    cout << "Enter station name: ";
    cin >> name;
    cout << "Enter station capacity: ";
    cin >> capacity;

    stations[stationCount] = {stationCount, name, capacity, 0};
    stationCount++;
    cout << "New station added successfully!" << endl;
}

// Function to remove a docking station
void removeStation()
 {
    int stationId;
    cout << "Enter the ID of the station to remove: ";
    cin >> stationId;

    if (stationId >= 0 && stationId < stationCount)
        {
        for (int i = stationId; i < stationCount - 1; i++)
         {
            stations[i] = stations[i + 1];
        }
        stationCount--;
        cout << "Station removed successfully!" << endl;
    }
    else
        {
        cout << "Invalid station ID." << endl;
    }
}

// Function to simulate daily activities
void simulateActivity()
 {
    srand(time(0));
    for (int i = 0; i < stationCount; i++)
        {
        int change = (rand() % 11) - 5; // Random change in bike availability (-5 to +5)
        updateAvailability(i, change);
    }
    cout << "Daily activity simulation complete." << endl;
}

// Function to generate a daily report
void generateDailyReport()
 {
    cout << "\nDaily Report:" << endl;
    for (int i = 0; i < stationCount; i++)
        {
        cout << "Station " << stations[i].name << ": " << stations[i].availableBikes << "/" << stations[i].capacity << " bikes available." << endl;
    }
}

// Function to add an edge to the graph
void addEdge(int src, int dest, int weight) {
    graph[src].push_back({dest, weight});
    graph[dest].push_back({src, weight}); // Assuming undirected graph
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(int start, int end) {
    vector<int> distance(stationCount, INT_MAX);
    vector<int> previous(stationCount, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        if (dist > distance[current]) continue;

        for (const auto& edge : graph[current]) {
            int next = edge.destination;
            int weight = edge.weight;

            if (distance[current] + weight < distance[next]) {
                distance[next] = distance[current] + weight;
                previous[next] = current;
                pq.push({distance[next], next});
            }
        }
    }

    if (distance[end] == INT_MAX) {
        cout << "No path found between the stations." << endl;
        return;
    }

    cout << "Shortest path from " << stations[start].name << " to " << stations[end].name << ":" << endl;
    vector<int> path;
    for (int at = end; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end()); // Reverse the path to get the correct order

    for (size_t i = 0; i < path.size(); i++) {
        cout << stations[path[i]].name;
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nTotal Distance: " << distance[end] << endl;
}

// Function to find the shortest path
void findShortestPath() {
    int start, end;
    cout << "Enter the starting station ID: ";
    cin >> start;
    cout << "Enter the destination station ID: ";
    cin >> end;

    if (start >= 0 && start < stationCount && end >= 0 && end < stationCount) {
        dijkstra(start, end);
    } else {
        cout << "Invalid station IDs. Please try again." << endl;
    }
}
// Admin menu
void adminMenu()
 {
    int choice;
    do {
        cout << "\nAdmin Menu:" << endl;
        cout << "1. Add Station" << endl;
        cout << "2. Remove Station" << endl;
        cout << "3. Simulate Daily Activity" << endl;
        cout << "4. Generate Daily Report" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
         {
        case 1:
            addStation();
            break;
        case 2:
            removeStation();
            break;
        case 3:
            simulateActivity();
            break;
        case 4:
            generateDailyReport();
            break;
        case 0:
            cout << "Returning to main menu." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
     while (choice != 0);
}
// Main program
int main() {
    // Initialize some stations and paths for demonstration
    stations[0] = {0, "Central Station", 20, 15};
    stations[1] = {1, "North Station", 15, 10};
    stations[2] = {2, "South Station", 10, 5};

    // Adding edges between stations
    addEdge(0, 1, 5); // Central to North with a distance of 5
    addEdge(1, 2, 10); // North to South with a distance of 10
    addEdge(0, 2, 15); // Central to South with a distance of 15

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            viewDockingStations();
            break;
        case 4:
            rentBike();
            break;
        case 5:
            returnBike();
            break;
        case 6:
            showRentalPrice();
            break;
        case 7:
            viewInvoices();
            break;
        case 8:
            saveInvoices();
            break;
        case 9:
            leaveFeedback();
            break;
        case 10:
            viewFeedback();
            break;
        case 11:
            logoutUser();
            break;
        case 12:
            adminMenu();
            break;
        case 13:
            findShortestPath();
            break;
        case 0:
            cout << "Thank you for using the E-Bike Management System! Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}

// Function to display the menu
void displayMenu() {
    cout << "\nE-Bike Management System" << endl;
    cout << "1. Register User" << endl;
    cout << "2. Login" << endl;
    cout << "3. View Docking Stations" << endl;
    cout << "4. Rent Bike" << endl;
    cout << "5. Return Bike" << endl;
    cout << "6. View Rental Price" << endl;
    cout << "7. View Invoices" << endl;
    cout << "8. Save Invoices" << endl;
    cout << "9. Leave Feedback" << endl;
    cout << "10. View Feedback" << endl;
    cout << "11. Logout" << endl;
    cout << "12. Admin Menu" << endl;
    cout << "13. Find Shortest Path" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}
void viewDockingStations()
 {
    cout << "\nAvailable Docking Stations:" << endl;
    for (int i = 0; i < stationCount; i++)
        {
        cout << "Station " << stations[i].id << " - " << stations[i].name << " (Capacity: " << stations[i].capacity << ", Bikes Available: " << stations[i].availableBikes << ")" << endl;
    }
}

void rentBike() {
    if (!loggedInUser) {
        cout << "You need to be logged in to rent a bike." << endl;
        return;
    }

    int stationId, bikes;
    cout << "Enter the station ID: ";
    cin >> stationId;
    cout << "Enter the number of bikes to rent: ";
    cin >> bikes;

    if (stationId >= 0 && stationId < stationCount && bikes > 0 && stations[stationId].availableBikes >= bikes) {
        stations[stationId].availableBikes -= bikes;
        double price = getPrice() * bikes;
        addInvoice(stationId, bikes, price);
        cout << "Successfully rented " << bikes << " bike(s) from " << stations[stationId].name << "." << endl;
    } else {
        cout << "Invalid request. Please check availability and try again." << endl;
    }
}

void returnBike() {
    if (!loggedInUser)
        {
        cout << "You need to be logged in to return a bike." << endl;
        return;
    }

    int stationId, bikes;
    cout << "Enter the station ID: ";
    cin >> stationId;
    cout << "Enter the number of bikes to return: ";
    cin >> bikes;

    if (stationId >= 0 && stationId < stationCount && bikes > 0)
        {
        stations[stationId].availableBikes += bikes;
        cout << "Successfully returned " << bikes << " bike(s) to " << stations[stationId].name << "." << endl;
    }
     else
        {
        cout << "Invalid request. Please check the station ID and try again." << endl;
    }
}

void showRentalPrice()
 {
    cout << "The rental price per bike is: Rs" << getPrice() << endl;
}

