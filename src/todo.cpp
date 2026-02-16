#include "todo.hpp"

#include <utility> // std::move

std::size_t TodoList::add(std::string text) {
  TodoItem item;
  item.id = next_id_;
  next_id_ += 1;

  item.text = std::move(text); 
  item.done = false;

  items_.push_back(std::move(item));

  return items_.back().id;
}

bool TodoList::mark_done(std::size_t id) {
  for (std::size_t i = 0; i < items_.size(); ++i) {
    TodoItem& item = items_[i]; 
    if (item.id == id) {
      item.done = true;
      return true;
    }
  }
  return false;
}

bool TodoList::remove(std::size_t id) {
  for (std::size_t i = 0; i < items_.size(); ++i) {
    if (items_[i].id == id) {
      items_.erase(items_.begin() + static_cast<std::ptrdiff_t>(i));
      return true;
    }
  }
  return false;
}

const std::vector<TodoItem>& TodoList::items() const noexcept {
  return items_;
}
