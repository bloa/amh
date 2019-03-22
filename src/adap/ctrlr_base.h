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
  class ctrlr_base {
  public:
    virtual void setup(int k) {
      current_index = k;
    }

    virtual void update() {}

    virtual int get_index() {
      return current_index;
    }

  protected:
    int current_index = 0;
  };
}
