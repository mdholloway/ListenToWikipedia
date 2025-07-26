package org.mdholloway.listentowikipedia.ui.main

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import org.mdholloway.listentowikipedia.databinding.FragmentRecentChangesBinding
import org.mdholloway.listentowikipedia.databinding.ItemRecentChangesBinding
import org.mdholloway.listentowikipedia.viewmodel.RecentChangesViewModel

class RecentChangesFragment : Fragment() {

    private var _binding: FragmentRecentChangesBinding? = null

    // This property is only valid between onCreateView and
    // onDestroyView.
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        val viewModel = ViewModelProvider(this).get(RecentChangesViewModel::class.java)
        _binding = FragmentRecentChangesBinding.inflate(inflater, container, false)
        val root: View = binding.root

        val recyclerView = binding.recyclerviewTransform
        val adapter = RecentChangesAdapter()
        recyclerView.adapter = adapter

        viewModel.recentChangesList.observe(viewLifecycleOwner) { list ->
            adapter.submitList(list)
        }
        viewModel.startListeningToRecentChanges()

        return root
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    class RecentChangesAdapter :
        ListAdapter<String, RecentChangesViewHolder>(object : DiffUtil.ItemCallback<String>() {
            override fun areItemsTheSame(oldItem: String, newItem: String): Boolean =
                oldItem == newItem

            override fun areContentsTheSame(oldItem: String, newItem: String): Boolean =
                oldItem == newItem
        }) {

        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): RecentChangesViewHolder {
            val binding = ItemRecentChangesBinding.inflate(LayoutInflater.from(parent.context))
            return RecentChangesViewHolder(binding)
        }

        override fun onBindViewHolder(holder: RecentChangesViewHolder, position: Int) {
            holder.textView.text = getItem(position)
        }
    }

    class RecentChangesViewHolder(binding: ItemRecentChangesBinding) :
        RecyclerView.ViewHolder(binding.root) {
        val textView: TextView = binding.textViewItemTransform
    }
}