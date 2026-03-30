#ifndef GLOBALS_H
#define GLOBALS_H
#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <map>
#include <vector>

enum class Color {
    Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
    BrightRed, BrightGreen, BrightYellow, BrightBlue
};
enum class Style {
    Bold = 1, Dim, Italic, Underline, Strikethrough
};
enum class Type {
    Project, Task
};
enum class Action {
    Create, Edit, Delete
};
enum class Status {
    Todo, InProgress, Completed
};
enum class Priority {
    Low, Medium, High
};

struct ColorPair{
    Color fg;
    Color bg;
};

const std::map<Priority, ColorPair> priorityColors = {
    {Priority::Low, {Color::Magenta, Color::Green}},
    {Priority::Medium, {Color::Black, Color::Yellow}},
    {Priority::High, {Color::White, Color::Red}}
};
const std::map<Priority, std::string> priorityStr = {
    {Priority::Low, "Low"},
    {Priority::Medium, "Medium"},
    {Priority::High, "High"}
};
const std::map<Status, ColorPair> statusColor = {
    {Status::Todo, {Color::Black, Color::Yellow}},
    {Status::InProgress, {Color::Cyan, Color::Blue}},
    {Status::Completed, {Color::Magenta, Color::Green}}
};
const std::map<Status, std::string> statusStr = {
    {Status::Todo, "Todo"},
    {Status::InProgress, "InProgress"},
    {Status::Completed, "Completed"}
};
#endif // GLOBALS_H
