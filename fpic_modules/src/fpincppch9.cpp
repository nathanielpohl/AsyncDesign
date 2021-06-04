// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch9.h"

#include <glog/logging.h>

#include <iostream>
#include <numeric>
#include <string>
#include <variant>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh9::FPInCppCh9(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh9::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
int FPInCppCh9::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Scratch pad from Chapter 9        ####";
  LOG(INFO) << "###################################################";

  {
    // Word count.
    std::string text = "There are five words here.";
    std::istringstream text_stream(text);
    unsigned count =
        std::distance(std::istream_iterator<std::string>(text_stream), {});
    LOG(INFO) << "Text: \"" << text << "\"";
    LOG(INFO) << "Word count: " << std::to_string(count);
  }

  LOG(INFO) << "###################################################";

  {
    // Sum type state machine for Tennis.
    class Tennis {
     private:
      enum class points { love, fifteen, thirty };

      enum class player { player_1, player_2 };

      struct normal_scoring {
        points player_1_points;
        points player_2_points;
      };

      struct forty_scoring {
        player leading_player;
        points other_player_points;
      };

      struct duce_scoring {};

      struct advantage_scoring {
        player player_with_advantage;
      };

      struct winner_scoring {
        player winner;
      };

     public:
      Tennis() {}

      void PointForPlayer(const player player_scored) {
        if (auto normal = std::get_if<normal_scoring>(&state_)) {
          if (player_scored == player::player_1) {
            if (normal->player_1_points == points::love) {
              normal->player_1_points = points::fifteen;
            } else if (normal->player_1_points == points::fifteen) {
              normal->player_1_points = points::thirty;
            } else {
              state_ = forty_scoring(player::player_1, normal->player_2_points);
            }
          } else {
            if (normal->player_2_points == points::love) {
              normal->player_2_points = points::fifteen;
            } else if (normal->player_2_points == points::fifteen) {
              normal->player_2_points = points::thirty;
            } else {
              state_ = forty_scoring(player::player_2, normal->player_1_points);
            }
          }
        } else if (auto forty = std::get_if<forty_scoring>(&state_)) {
          if (player_scored == forty->leading_player) {
            state_ = winner_scoring(forty->leading_player);
          } else {
            if (forty->other_player_points == points::love) {
              forty->other_player_points = points::fifteen;
            } else if (forty->other_player_points == points::fifteen) {
              forty->other_player_points = points::thirty;
            } else {
              state_ = duce_scoring();
            }
          }
        } else if (auto duce = std::get_if<duce_scoring>(&state_)) {
          if (duce) {
            // Unused variable duce error.
          }

          state_ = advantage_scoring(player_scored);
        } else if (auto advantage = std::get_if<advantage_scoring>(&state_)) {
          if (player_scored == advantage->player_with_advantage) {
            state_ = winner_scoring(advantage->player_with_advantage);
          } else {
            state_ = duce_scoring();
          }
        } else {
          LOG(INFO) << "What are you doing, the game is already won!";
        }
      }

     private:
      std::variant<normal_scoring, forty_scoring, duce_scoring,
                   advantage_scoring, winner_scoring>
          state_{normal_scoring(points::love, points::love)};
    };

    Tennis match;
  }

  return 0;
}
}  // namespace fpic_modules
