#pragma once /* Tells compiler to only include this header once per translation */

#include <cstddef> /* For size_t and next_id_ */
#include <string> 
#include <string_view>
#include <vector> 

struct TodoItem {
  std::size_t id; /* size_t is the standard choice for ids, counts, and indexes*/
  std::string text;
  bool done;
};

class TodoList {
 public:
  std::size_t add(std::string text);

  bool mark_done(std::size_t id);

  bool remove(std::size_t id);

  /* The & after the vector is so that we can just look at it and it doesnt copy, without it, it would copy the entire vector */
  /* items() gives read only to the todo items in private */
  const std::vector<TodoItem>& items() const noexcept;

 private:
  std::vector<TodoItem> items_;
  std::size_t next_id_{1}; /* {1} is a default member initializer, so it automatically starts at 1 without needing to write a constructor */
};

