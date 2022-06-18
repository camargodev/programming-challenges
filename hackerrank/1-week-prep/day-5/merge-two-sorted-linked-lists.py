def mergeLists(head1, head2):
    last = None
    current = None
    merged_list_head = None
    while head1 is not None and head2 is not None:
        if head1.data < head2.data:
            if merged_list_head is None:
                merged_list_head = head1
            current, last, head1 = consume_list(current, last, head1)
        else:
            if merged_list_head is None:
                merged_list_head = head2
            current, last, head2 = consume_list(current, last, head2)
    if head1 is None:
        while head2 is not None:
            current, last, head2 = consume_list(current, last, head2)
    if head2 is None:
        while head1 is not None:
            current, last, head1 = consume_list(current, last, head1)
             
    return merged_list_head
            
def consume_list(current, last, list_head):
    current = list_head
    if last is not None:
        last.next = current
    last = current
    list_head = list_head.next
    return current, last, list_head