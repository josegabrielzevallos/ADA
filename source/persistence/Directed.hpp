#ifndef SOURCE_DIRECTEDGRAPH_HPP_
#define SOURCE_DIRECTEDGRAPH_HPP_

#include <cstddef>
#include <iostream>

namespace ADE {
	
	template <typename Type>
	class Node {
	public:
		typedef Type data_type;
		
		Node(data_type data, std::size_t const& out_ptrs_size)
			: data_(new data_type(data)),
			out_ptrs_size_(out_ptrs_size),
			forward_(new Node<Type>*[out_ptrs_size]()) {}
		
		virtual ~Node() {}
		
		/**
		*  \brief Access specified element
		*
		*  Returns a reference to the element at specified location position. If id
		* is not within the range of the container an exception of type
		* std::out_of_range is thrown. If no node exist at the location
		* std::logic_error is thrown.
		*
		*/
		Node& operator[](std::size_t id) const {
			if (out_ptrs_size_ < id) {
				throw std::out_of_range("Index out of node edges range.");
			}
			if (!forward_[id]) {
				throw std::logic_error("Access to null reference.");
			}
			return *forward_[id];
		}
		void operator =(Node<data_type> &a)
		{
			data_ = a.data_;
			for(int i = 0 ;i<out_ptrs_size_;++i){
				forward_[i] = a.forward_[i];  
			}
			//forward_ = a.forward_;
			out_ptrs_size_ = a.out_ptrs_size_;     
		}
		
		data_type* data_;
		Node** forward_;
		std::size_t out_ptrs_size_;
	};
	
	template <typename Type, typename Node = Node<Type>>
	class DirectedGraph {
	public:
		typedef Type data_type;
		
		DirectedGraph(data_type const data, std::size_t const& out_ptrs_size, std::size_t const& in_ptrs_size)
			: root_ptr_(new Node(data, out_ptrs_size, in_ptrs_size)),
			out_ptrs_size_(out_ptrs_size) {}
		
		virtual ~DirectedGraph() {}
		
		Node* get_root_ptr() { return root_ptr_; }
		
		/**
		*  \brief Inserts element
		*
		*  Inserts elements at the specified node in the container at location id and
		* returns the vertex pointer for the new vertex.
		*
		*/
		Node* insert_vertex(data_type const data, Node* u, std::size_t position) {
			if (u->out_ptrs_size_ != out_ptrs_size_) {
				throw std::logic_error("Node with different number of out pointers.");
			}
			if (out_ptrs_size_ < position) {
				throw std::out_of_range("Insert position out of node edges range.");
			}
			Node* next_node_ptr = dynamic_cast<Node*>(u->forward_[position]);
			Node* new_node = new Node(data, out_ptrs_size_);
			new_node->forward_[position] = next_node_ptr;
			u->forward_[position] = new_node;
			return dynamic_cast<Node*>(u->forward_[position]);
		}
		
		/**
		*  \brief Attachs two nodes
		*
		*  Adds edge from u to v and throws and exception oof type std::out_of_range
		* if position is not within the range of u. nodes,
		*
		*/
		void add_edge(Node* u, Node* v, std::size_t position) {
			if (u->out_ptrs_size_ < position) {
				throw std::out_of_range("Position out of first argument node.");
			}
			u->forward_[position] = v;
		}
		
	protected:
			Node* root_ptr_;
			std::size_t out_ptrs_size_;
	};
	
}  // namespace ADE

#endif  // SOURCE_DIRECTEDGRAPH_HPP_
