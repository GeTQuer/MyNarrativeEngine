#include "narrative/NarrativeEngine.hpp"
#include "narrative/StoryLoader.hpp"
using namespace std;
using namespace narrative;

int main() {
    NarrativeEngine engine;
    StoryLoader::load("stories/trapped_cycle.json", engine);
//     NarrativeEngine engine;
//
//     engine.addNode(DialogueNode{
//         "start",
//         "Character1",
//         "Hi",
//         "Replic2"
//     });
//
//     engine.addNode(DialogueNode{
//         "Replic2",
//         "Character2",
//         "KYS",
//         "choiceChar1"
//     });
//
//     engine.addNode(ChoiceNode{
//         "choiceChar1",
//         {
//             {"What?","answer1"},
//             {"Ok","answer2"},
//             {"Goodbye","answer3"}
//         }
//     });
//
//     engine.addNode(DialogueNode{
//     "answer1",
//     "Character1",
//     "What do you mean?",
//     "end"
// });
//
//     engine.addNode(DialogueNode{
//         "answer2",
//         "Character1",
//         "Alright.",
//         "end"
//     });
//
//     engine.addNode(DialogueNode{
//         "answer3",
//         "Character1",
//         "See you.",
//         "end"
//     });
//
//     engine.addNode(EndNode{"end"});
//
//     engine.start("start");
//
//     while (!engine.isFinished()) {
//         const Node& node = engine.current();
//
//         if (holds_alternative<DialogueNode>(node)) {
//             const DialogueNode& dialogueNode = get<DialogueNode>(node);
//             cout << dialogueNode.speaker << ": " << dialogueNode.text << endl;
//             engine.advance();
//         }else if (holds_alternative<ChoiceNode>(node)) {
//             const ChoiceNode& choiceNode = get<ChoiceNode>(node);
//
//             for (size_t i = 0; i < choiceNode.choices.size(); i++) {
//                 cout << i + 1 << ". "
//                      << choiceNode.choices[i].text << endl;
//             }
//             size_t answer;
//
//             cout << "Your choice: ";
//
//             if (!(cin >> answer) ||
//                 answer == 0 ||
//                 answer > choiceNode.choices.size()) {
//
//                 cout << "Invalid choice!" << endl;
//                 return 1;
//                 }
//
//             engine.selectChoice(answer - 1);
//         }
//     }
//     return 0;
}
