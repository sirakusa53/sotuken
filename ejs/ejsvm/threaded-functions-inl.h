/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */

static header_t get_threaded_header(header_t *hdrp);

static bool is_reference(void **pptr) {
  header_t hdr;
  hdr.threaded = (uintptr_t) pptr;
  return hdr.identifier == 0;
}

static void thread_reference(void **ref) {
#ifdef USE_EMBEDDED_INSTRUCTION
  assert(!in_mbed_flash(ref));
  assert(!in_mbed_flash(*ref));
#endif /* USE_EMBEDDED_INSTRUCTION */

#ifdef DEBUG
  {
    if (!is_reference(ref)) {
      LOG_EXIT("refernece %p is unthreadable address.", ref);
    }
  }
#endif /* DEBUG */

  assert(get_threaded_header(payload_to_header(*ref)).markbit);

  if (*ref != NULL) {
#ifdef GC_DEBUG
    if (!is_reference((void **) *ref)) {
      LOG_EXIT("*ref value : 0x%016" PRIxPTR " (at %p) is not reference", (uintptr_t) *ref, ref);
    }
    if (!in_js_space(*ref)) {
      LOG_EXIT("*ref value : 0x%016" PRIxPTR " (at %p) is not in js_space", (uintptr_t) *ref, ref);
    }
#endif /* GC_DEBUG */

    void *payload = *ref;
    header_t *hdrp = payload_to_header(payload);
    assert((!is_reference((void **) hdrp))? (hdrp->markbit == 1) : 1);

    uintptr_t val = hdrp->threaded;
    hdrp->threaded = (uintptr_t) ref;
    *ref = (void *) val;
  }
}

static header_t get_threaded_header(header_t *hdrp)
{
  header_t hdr = *hdrp;
  while(!hdr.identifier)
    hdr.threaded = *(uintptr_t *) hdr.threaded;

  return hdr;
}

static bool get_threaded_header_markbit(header_t *hdrp) {
  /* If header is threaded, it must be marked */
  if (is_reference((void **) hdrp->threaded)) {
#ifdef GC_DEBUG
    while(is_reference((void **) hdrp->threaded)) {
      hdrp = (header_t *) hdrp->threaded;
    }
    assert(hdrp->markbit != 0);
#endif /* GC_DEBUG */
    return true;
  }
  return hdrp->markbit != 0;
}

static void update_reference(uintjsv_t tag, void *ref_, void *addr) {
  header_t *hdrp = payload_to_header(ref_);
  uintjsv_t value = put_ptag((uintjsv_t) addr, ((PTag) {tag}));

  void **ref = (void **) hdrp->threaded;
  while(is_reference(ref)) {
    void **next = (void **) *ref;
    *ref = (void *) value;
    ref = next;
  }
  hdrp->threaded = (uintptr_t) ref;
}

