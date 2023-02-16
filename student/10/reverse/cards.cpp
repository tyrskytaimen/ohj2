#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if( top_ == nullptr ) {
        return false;
    }
    else if( top_->data == id ) {
        top_ = top_->next;
        return true;
    }

    std::shared_ptr<Card_data> to_be_removed = top_;
    while( to_be_removed != 0 ) {
        if( to_be_removed->next->next == 0 ) {
            if( to_be_removed->next->data == id ) {
                 to_be_removed->next = 0;
                 return true;
            }
            else {
                return false;
            }
        }
        if( to_be_removed->next->data == id ) {
            to_be_removed->next = to_be_removed->next->next;
            return true;
        }
        to_be_removed = to_be_removed->next;
    }
    return false;
}

void Cards::reverse()
{
    if( top_ == 0 or  top_->next == 0 ) {
        return;
    }
    else if( top_->next->next == 0 ) {
        top_->next->next = top_;
        top_ = top_->next;
        top_->next->next = 0;
        return;
    }

    std::shared_ptr<Card_data> previous = top_;
    std::shared_ptr<Card_data> current = previous->next;
    std::shared_ptr<Card_data> following = current->next;

    while( following != 0 ) {
        current->next = previous;
        previous = current;
        current = following;
        following = following ->next;
    }
    current->next = previous;
    top_->next = 0;
    top_ = current;

}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
