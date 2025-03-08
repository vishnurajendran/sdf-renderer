//
// Created by ssj5v on 27-09-2024.
//

#pragma once
#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <sstream>

#include "string"

bool readFile(const std::string& path, std::string& data);
std::string getFileExtension(const std::string& path);

#endif //FILEIO_H
