// Copyright (c) 2015 Thiago Pereira Bueno
// All Rights Reserved.
//
// This file is part of DBN library.
//
// DBN is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DBN is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DBN.  If not, see <http://www.gnu.org/licenses/>.

#include "domain.h"

#include <vector>

namespace dbn {

    Domain::Domain(Variable **scope, unsigned width) : _scope(scope), _width(width) {
        _size = 1;
        for (unsigned i = 0; i < _width; ++i) {
            _size *= _scope[i]->size();
            _var_to_index[_scope[i]->id()] = i;
        }
    }

    Domain::~Domain() {
        delete[] _scope;
    }

    unsigned Domain::position(unsigned instantiation[]) {
        unsigned pos = 0;
        unsigned offset = 1;
        for (unsigned i = 0; i < _width; ++i) {
            pos += instantiation[i] * offset;
            offset *= _scope[i-1]->size();
        }
        return pos;
    }

    Domain* Domain::union_of(const Domain* d1, const Domain* d2) {
        std::vector<Variable* > scope;
        unsigned total_width;

        unsigned width1 = d1->width();
        total_width = width1;

        for (unsigned i = 0; i < width1; ++i) {
            scope.push_back((*d1)[i]);
        }

        unsigned width2 = d2->width();
        for (unsigned i = 0; i < width2; ++i) {
            if (_var_to_index.find((*d2)[i]->id()) == _var_to_index.end()) {
                scope.push_back((*d2)[i]);
                total_width++;
            }
        }

        return new Domain(&scope[0], total_width);
    }

    Domain* Domain::union_of(const Domain* d1, const Domain* d2, const Variable* v) {
        std::vector<Variable* > scope;
        unsigned total_width;

        unsigned width1 = d1->width();
        total_width = width1;

        for (unsigned i = 0; i < width1; ++i) {
            if (_var_to_index.find((*d1)[i]->id()) == _var_to_index.end()) {
                scope.push_back((*d1)[i]);
            }
        }

        unsigned width2 = d2->width();
        for (unsigned i = 0; i < width2; ++i) {
            if (_var_to_index.find((*d2)[i]->id()) == _var_to_index.end()) {
                scope.push_back((*d2)[i]);
                total_width++;
            }
        }

        return new Domain(&scope[0], total_width);
    }

    std::ostream& operator<<(std::ostream &o, const Domain &d) {
        unsigned width = d.width();
        o << "Domain{";
        unsigned i;
        for (i = 0; i < width-1; ++i) {
            o << d[i]->id() << ", ";
        }
        o << d[i]->id() << "}";
        return o;
    }

}