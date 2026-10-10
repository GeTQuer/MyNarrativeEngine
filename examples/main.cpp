
#include <iostream>
#include "narrative/NarrativeEngine.hpp"

using namespace std;
using namespace narrative;

int main() {
    NarrativeEngine engine;

    engine.addNode(DialogueNode{
        "intro",
        "Robert",
        "Hello, Mandy!",
        "second"
    });

    engine.addNode(DialogueNode{
        "second",
        "Mandy",
        "Hello, Robert!",
        "end"
    });

    engine.addNode(EndNode{"end"});

    engine.start("intro");

    const Node& node = engine.current();

    if (holds_alternative<DialogueNode>(node)) {
        const DialogueNode& dialogue = get<DialogueNode>(node);

        cout << dialogue.speaker << ": "
             << dialogue.text << endl;
    }

    return 0;
}
