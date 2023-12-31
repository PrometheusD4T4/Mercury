//
// Created by rokas on 7/20/23.
//

#include "DBWrapper/GraphDB.hpp"

#include <iostream>

GraphDB::GraphDB(const std::string& host, uint16_t port, bool ssl) {
    mg::Client::Init();

    // Construct Params
    mg::Client::Params clientParams;
    clientParams.host = host;
    clientParams.port = port;
    clientParams.use_ssl = ssl;

    // Connection
    this->client = mg::Client::Connect(clientParams);

    if (!this->client) {
        std::cerr << "Failed to connect!\n";
        return;
    } else {
        this->ready = true;
    }
}

GraphDB::~GraphDB() {
    this->client.reset(nullptr);

    mg::Client::Finalize();
}

std::unique_ptr<mg::Client>* GraphDB::GetClient() { return &this->client; }

// Executes a query, which returns no values
void GraphDB::Execute(const std::string& query) {
    if (!this->client->Execute(query)) {
        std::cerr << "Query failed." << std::endl;
        std::exit(1);
    }

    this->client->DiscardAll();
}

void GraphDB::ClearDatabaseData() { this->Execute("MATCH (n) DETACH DELETE n;"); }

bool GraphDB::IsReady() {
    return this->ready;
}
