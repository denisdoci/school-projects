package edu.uic.denisdoci.doci2project3a3;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;

/*
    Note much of this was taken from Prof. Ugo Buy's Example on fragments
 */
public class BasketballWebviewFragment extends Fragment {

	private static final String TAG = "BasketballWebviewFragment";

	private WebView mQuoteView = null;
	private int mCurrIdx = -1;
	private int mQuoteArrLen;

	int getShownIndex() {
		return mCurrIdx;
	}

	// Show the Quote string at position newIndex
	void showQuoteAtIndex(int newIndex) {
		if (newIndex < 0 || newIndex >= mQuoteArrLen)
			return;
		mCurrIdx = newIndex;
		mQuoteView.loadUrl(BasketballActivity.mQuoteArray[mCurrIdx]);
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	// Called to create the content view for this Fragment
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
							 Bundle savedInstanceState) {

		// Inflate the layout defined in webview// The last parameter is false because the returned view does not need to be attached to the container ViewGroup
		return inflater.inflate(R.layout.webview,
				container, false);
	}

	// Set up some information about the mQuoteView TextView 
	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);

		mQuoteView = (WebView) getActivity().findViewById(R.id.quoteView);
		mQuoteArrLen = BasketballActivity.mQuoteArray.length;
	}

	@Override
	public void onStart() {
		super.onStart();
	}
	
	@Override
	public void onResume() {
		super.onResume();
	}

	
	@Override
	public void onPause() {
		super.onPause();
	}

	@Override
	public void onStop() {
		super.onStop();
	}
	
	@Override
	public void onDetach() {
		super.onDetach();
	}

	
	@Override
	public void onDestroy() {
		super.onDestroy();
	}

	@Override
	public void onDestroyView() {
		super.onDestroyView();
	}

}
