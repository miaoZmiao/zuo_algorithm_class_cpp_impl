#pragma once

#include "utility_func.hpp"


namespace Code02_DeleteGivenValue {
	struct LinkNode {
		LinkNode() {}
		LinkNode(int v) :value(v) {

		}
		int value;
		LinkNode * next = nullptr;

	};

	// head = removeValue(head, 2);
	LinkNode * removeValue(LinkNode * head, int num) {
		// head来到第一个不需要删的位置
		while (head != nullptr) {
			if (head->value != num) {
				break;
			}
			head = head->next;
		}
		// 1 ) head == null
		// 2 ) head != null
		LinkNode * pre = head;
		LinkNode * cur = head;
		while (cur != nullptr) {
			if (cur->value == num) {
				pre->next = cur->next;
			}
			else {
				pre = cur;
			}
			cur = cur->next;
		}
		return head;
	}

}