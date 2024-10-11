#include <iostream>
#include <memory>
#include <random>
#include <vector>

class RandomVariable {
 public:
  virtual unsigned roll() = 0;
  virtual ~RandomVariable() = default;
};

class Dice : virtual public RandomVariable {
 public:
  Dice(unsigned max_, unsigned seed) : max(max_), dstr(1, max_), reng(seed) {}
  Dice(Dice &dice)
      : max(dice.get_max()), dstr(dice.get_dstr()), reng(dice.get_reng()) {}

  unsigned roll() override { return dstr(reng); }

  unsigned get_max() { return max; }

  std::uniform_int_distribution<unsigned> get_dstr() { return dstr; }

  std::default_random_engine get_reng() { return reng; }

 private:
  unsigned max;
  std::uniform_int_distribution<unsigned> dstr;
  std::default_random_engine reng;
};

double expected_value(RandomVariable &rv, unsigned number_of_rolls) {
  auto accum = 0llu;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) accum += rv.roll();
  return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

class PenaltyDice : public Dice {
 public:
  PenaltyDice(Dice &d) : Dice(d), dice(d) {}

  unsigned roll() override { return std::min(dice.roll(), dice.roll()); }

 private:
  Dice &dice;
};

class BonusDice : public Dice {
 public:
  BonusDice(Dice &d) : Dice(d), dice(d) {}

  unsigned roll() override { return std::max(dice.roll(), dice.roll()); }

 private:
  Dice &dice;
};

class DoubleDice : public PenaltyDice, public BonusDice {
 public:
  DoubleDice(PenaltyDice pd_, BonusDice bd_)
      : PenaltyDice(pd_), BonusDice(bd_), pd(pd_), bd(bd_) {}

  unsigned roll() override { return PenaltyDice::roll() + BonusDice::roll(); }

 private:
  PenaltyDice pd;
  BonusDice bd;
};

double value_probability(unsigned value, RandomVariable &rv,
                         unsigned number_of_rolls = 1) {
  unsigned count = 0;

  for (unsigned i = 0; i < number_of_rolls; ++i) {
    if (rv.roll() == value) {
      count++;
    }
  }

  return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}

void print_histogram(unsigned sides, unsigned rolls) {
  Dice normalDice(sides, 42);
  PenaltyDice penaltyDice(normalDice);
  BonusDice bonusDice(normalDice);
  DoubleDice doubleDice(penaltyDice, bonusDice);

  std::vector<double> normalProbabilities(sides + 1, 0);
  std::vector<double> penaltyProbabilities(sides + 1, 0);
  std::vector<double> bonusProbabilities(sides + 1, 0);
  std::vector<double> doubleProbabilities(sides + 1, 0);

  for (unsigned value = 1; value <= sides; ++value) {
    normalProbabilities[value] = value_probability(value, normalDice, rolls);
  }

  for (unsigned value = 1; value <= sides; ++value) {
    penaltyProbabilities[value] = value_probability(value, penaltyDice, rolls);
  }

  for (unsigned value = 1; value <= sides; ++value) {
    bonusProbabilities[value] = value_probability(value, bonusDice, rolls);
  }

  for (unsigned value = 1; value <= sides; ++value) {
    doubleProbabilities[value] = value_probability(value, doubleDice, rolls);
  }

  std::cout << "Value\tNormal\tPenalty\tBonus\tDouble\n";
  for (unsigned value = 1; value <= sides; ++value) {
    std::cout << value << "\t" << normalProbabilities[value] << "\t"
              << penaltyProbabilities[value] << "\t"
              << bonusProbabilities[value] << "\t" << doubleProbabilities[value]
              << "\n";
  }
}

int main() {
  unsigned sides = 100;
  unsigned rolls = 10000;

  print_histogram(sides, rolls);

  return 0;
}

//   g++ -Wall -Wextra -Wno-sign-conversion -Wshadow
//   -fsanitize=address,undefined