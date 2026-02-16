#include <iostream>
#include <string>

#include "todo.hpp"


static void print_list(const TodoList& list) {
  const std::vector<TodoItem>& items = list.items();

  if (items.empty()) {
    std::cout << "(no todos)\n";
    return;
  }

  for (std::size_t i = 0; i < items.size(); ++i) {
    const TodoItem& item = items[i]; // reference, no copy
    std::cout << item.id << " - " << (item.done ? "[x] " : "[ ] ") << item.text << '\n';
  }
}


static bool starts_with(const std::string& s, const std::string& prefix) {
  if (s.size() < prefix.size()) return false;
  return s.compare(0, prefix.size(), prefix) == 0;
}

int main() {
  TodoList list;

  std::cout << "Todo CLI\n";
  std::cout << "Commands:\n";
  std::cout << "  add <text>\n";
  std::cout << "  done <id>\n";
  std::cout << "  remove <id>\n";
  std::cout << "  list\n";
  std::cout << "  debug\n";
  std::cout << "  quit\n";

  std::string line;
  while (true) {
    std::cout << "> ";
    if (!std::getline(std::cin, line)) {
      break; // input ended
    }

    if (line.empty()) {
      continue;
    }

    if (starts_with(line, "add ")) {
      // English: "Take everything after 'add ' as the todo text."
      std::string text = line.substr(4);

      // English: "Add it to the list; move the text so we don't copy its characters."
      std::size_t id = list.add(std::move(text));

      std::cout << "added id=" << id << '\n';
      continue;
    }

    if (starts_with(line, "done ")) {
      std::string id_str = line.substr(5);
      std::size_t id = static_cast<std::size_t>(std::stoull(id_str));

      bool ok = list.mark_done(id);
      std::cout << (ok ? "marked done\n" : "id not found\n");
      continue;
    }

    if (starts_with(line, "remove ")) {
      std::string id_str = line.substr(7);
      std::size_t id = static_cast<std::size_t>(std::stoull(id_str));

      bool ok = list.remove(id);
      std::cout << (ok ? "removed\n" : "id not found\n");
      continue;
    }

    if (line == "list") {
      print_list(list);
      continue;
    }

    if (line == "quit") {
      break;
    }

    std::cout << "unknown command\n";
  }

  std::cout << "bye\n";
  return 0;
}
