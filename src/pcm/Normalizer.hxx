// SPDX-License-Identifier: LGPL-2.1
// Copyright The Music Player Daemon Project
// Based on AudioCompress (c)2007 busybee (http://beesbuzz.biz/

#pragma once

#include <cstddef>
#include <cstdint>
#include <span>

class PcmNormalizer {
	///! Target level (on a scale of 0-32767)
	static constexpr int target = 16384;

	//! The maximum amount to amplify by
	static constexpr int maxgain = 32;

	//! How much inertia ramping has
	static constexpr int smooth = 8;

        //! History of the peak values
        int *const peaks;

        //! History of the gain values
        int *const gain;

	std::size_t pos = 0;
        const std::size_t bufsz;

public:
	PcmNormalizer(std::size_t history=400) noexcept
		:peaks(new int[history]{}),
		 gain(new int[history]{}),
		 bufsz(history)
	{
	}

	~PcmNormalizer() noexcept {
		delete[] peaks;
		delete[] gain;
	}

	//! Process 16-bit signed data
	void ProcessS16(std::span<int16_t> audio) noexcept;
};

//! TODO: Compressor_Process_int32, Compressor_Process_float, others as needed

//! TODO: functions for getting at the peak/gain/clip history buffers (for monitoring)
