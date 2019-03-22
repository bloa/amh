/*
  Copyright (C) ORKAD team, CRIStAL, University of Lille, 2017
  Aymeric Blot

  This software is governed by the CeCILL-C license.
  You can use, modify and/ or redistribute the software under the
  terms of the CeCILL-C license as circulated by CEA, CNRS and INRIA
  at the following URL "http://www.cecill.info".
 */

#pragma once

namespace amh {
  class ctrlr_greedy : public ctrlr_feed<double> {
  public:
    ctrlr_greedy(double _alpha, double _epsilon) :
      alpha(_alpha), epsilon(_epsilon) {}

    void setup(int k) {
      if (k == 0)
        throw std::runtime_error("*** ERROR : zero options");
      size = k;
      est_payoffs.resize(0);
      current_index = 0;
      //for (int i=0; i<size; i++)
      //  est_payoffs.push_back(1);
      sum_payoffs = 0;//size;
    }

    void feed(double x) {
      int s = est_payoffs.size();
      if (s != size) {
        if (s != current_index)
          throw std::runtime_error("*** ERROR : bad init sequence");
        est_payoffs.push_back(x);
      } else {
        double tmp = est_payoffs[current_index];
        est_payoffs[current_index] = tmp + alpha*(x-tmp);
        if (est_payoffs[current_index] >= est_payoffs[max_payoff_id])
          max_payoff_id = current_index;
      }
      sum_payoffs = 0;
      for (unsigned int i=0; i<est_payoffs.size(); i++)
        sum_payoffs += est_payoffs[i];
    }

    void update() {
      if (est_payoffs.size() < size) {
        current_index = est_payoffs.size();
      } else {
        double x = rng.uniform();
        if (x > epsilon) {
          current_index = max_payoff_id;
        } else {
          current_index = rng.random(size-1);
          if (current_index >= max_payoff_id)
            current_index++;
        }
      }
    }

    int get_index() {
      return current_index;
    }

    double get_payoff(int k) {
      if (k < est_payoffs.size())
        return est_payoffs[k];
      else
        return 0.0;
    }

    void summary() {
      for (int i=0; i<est_payoffs.size(); i++)
        std::cout << est_payoffs[i] << " ";
      std::cout << std::endl;
    }

  protected:
    int current_index = 0;
    std::vector<double> est_payoffs;
    double sum_payoffs;
    double max_payoff_id;
    double alpha = 0.5;
    double epsilon = 0.5;
    int init = 0;
    int size = 0;
  };
}
